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

int			treat_expansions(t_process *p)
{
	int	i;
	int	ret;
	int	skip;
	int	fields;

	i = 0;
	ret = 0;
	if (!p->argv || !*p->argv)
		return (e_invalid_input);
	while (!ret && i < p->argc)
	{
		fields = 1;
		ret = treat_single_exp(p->argv + i, 1);
		if (!ret && empty_exp(p, i))
			continue ;
		ret = !ret ? field_split(p, i, &fields) : ret;
		while (!ret && fields--)
		{
			skip = 0;
			ret = !ret ? pathname_expansion(p, i, &skip) : ret;
			ret = !ret && !skip ? rm_quotes(p->argv + i, NO_QUOTE) : ret;
			i += skip ? skip : 1;
		}
	}
	return (e_success);
}
