#include "libft.h"
#include "shell.h"
#include "error.h"
#include "quotes.h"

static int	empty_exp(t_process *p, int i)
{
	if (p->argv[i][0])
		return (0);
	free(p->argv[i]);
	ft_memcpy(p->argv + i, p->argv + i + 1, (p->argc - i) * sizeof(char *));
	--p->argc;
	return (1);
}

static int	treat_word_expansion(t_process *p, int *i)
{
	int	ret;
	int	skip;
	int	fields;
	
	ret = 0;
	if (empty_exp(p, *i))
		return (ret);
	fields = 1;
	ret = field_split(p, *i, &fields);
	while (!ret && fields--)
	{
		skip = 0;
		ret = !ret ? pathname_expansion(p, *i, &skip) : ret;
		ret = !ret && !skip ? rm_quotes(p->argv + *i, NO_QUOTE) : ret;
		*i += skip ? skip : 1;
	}
	return (ret);
}

int			treat_expansions(t_process *p, int *only_assignments)
{
	int		i;
	int		ret;
	char	*equal;

	i = 0;
	ret = 0;
	if (!p->argv || !*p->argv)
		return (e_invalid_input);
	while (!ret && i < p->argc)
	{
		equal = is_valid_assignment(p->argv[i]);
		*only_assignments = !equal ? 0 : *only_assignments;
		ret = treat_single_exp(p->argv + i, 1, equal);
		if (!ret && equal)
			ret = rm_quotes(p->argv + i++, NO_QUOTE);
		else if (!ret)
			ret = treat_word_expansion(p, &i);
	}
	return (ret);
}
