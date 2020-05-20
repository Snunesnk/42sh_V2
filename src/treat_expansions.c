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
	if ((ret = treat_single_exp(p->argv + *i, 1, NULL)) || empty_exp(p, *i))
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

int			treat_expansions(t_process *p)
{
	int		i;
	int		ret;
	char	*equal;

	i = 0;
	ret = 0;
	if (!p->argv || !*p->argv)
		return (e_invalid_input);
	while (!ret && i < p->argc && (equal = is_valid_assignment(p->argv[i])))
	{
		++p->assignments_count;
		ret = treat_single_exp(p->argv + i, 1, equal);
		ret = !ret ? rm_quotes(p->argv + i++, NO_QUOTE) : ret;
	}
	while (!ret && i < p->argc)
		ret = treat_word_expansion(p, &i);
	return (ret);
}
