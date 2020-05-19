#include "libft.h"
#include "shell.h"
#include "error.h"
#include "quotes.h"

const struct s_tags	g_tags[] =
{
	{"${", &parameter_expansions, "}"},
	{"$", &dollar_expansions, ""},
	{"~", &tilde_expansion, ""},
	{"\0", NULL, NULL}
};

static char	*get_closest_exp(char *str, int tilde, int *ref, int *qmode)
{
	int		i;
	char	*ptr;
	char	*closest;
	int		tmp_qmode;
	int		orig_qmode;

	i = 0;
	*ref = -1;
	closest = NULL;
	orig_qmode = *qmode;
	while (*g_tags[i].opentag && (tilde || *g_tags[i].opentag != '~'))
	{
		tmp_qmode = orig_qmode;
		ptr = ft_strstr_qmode(str, g_tags[i].opentag,
			*g_tags[i].opentag == '~' ? NO_QUOTE : DQUOTE, &tmp_qmode);
		if (ptr && (!closest || ptr < closest))
		{
			*qmode = tmp_qmode;
			closest = ptr;
			*ref = i;
		}
		++i;
	}
	return (closest);
}

static int		replace_expansion(char **token, char **next, int ref)
{
	size_t	lcontent;
	char	*new;
	size_t	lnew;
	size_t	lprefix;
	int		ret;

	lcontent = 0;
	ret = e_success;
	lprefix = (size_t)((*next) - (*token));
	if (!(ret = g_tags[ref].f(&lcontent, next,
	g_tags[ref].opentag, g_tags[ref].closetag)))
	{
		lnew = lprefix + ft_strlen(*next);
		new = (char*)ft_memalloc(sizeof(char) * (lnew + 1));
		ft_strncat(new, *token, lprefix);
		ft_memdel((void**)token);
		ft_strcat(new, *next);
		ft_memdel((void**)next);
		*next = &(new)[lcontent + lprefix];
		*token = new;
		return (e_success);
	}
	return (ret);
}

static int		valid_tilde(const char *start, const char *tilde, int assignment)
{
	const char	*end;

	if (!start || !tilde || *tilde != '~')
		return (0);
	end = tilde + 1 + (tilde[1] == '+' || tilde[1] == '-');
	if (*end && !(*end == '/' || (assignment && *end == ':')))
		return (0);
	return (tilde == start || (assignment && tilde > start && *(tilde - 1) == ':'));
}

static int		expand_assignment_tildes(char **str, char *equal)
{
	int	ref;
	int	ret;
	int	qmode;
	char	*next;

	ret = e_success;
	next = equal;
	qmode = NO_QUOTE;
	while (!ret && (next = get_closest_exp(next, 1, &ref, &qmode)))
	{
		if (valid_tilde(equal, next, 1))
		{
			ret = replace_expansion(str, &next, ref);
			equal = ft_strchr(*str, '=');
		}
		else
			++next;
	}
	return (ret);
}

int			treat_single_exp(char **str, int tilde, char *equal)
{
	int		ref;
	int		ret;
	int		qmode;
	char	*next;

	ret = e_success;
	if (equal && tilde)
	{
		ret = expand_assignment_tildes(str, equal + 1);
		tilde = 0;
	}
	next = equal ? ft_strchr(*str, '=') : *str;
	qmode = NO_QUOTE;
	while (!ret && (next = get_closest_exp(next, tilde, &ref, &qmode)))
	{
		if (tilde && !valid_tilde(*str, next, 0))
			tilde = 0;
		if (!tilde && *next == '~')
			continue ;
		ret = replace_expansion(str, &next, ref);
	}
	if (ret)
		psherror(ret, *str, e_cmd_type);
	return (ret);
}
