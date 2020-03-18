#include "ft_readline.h"

t_data	*init_data(void)
{
	t_data	*new_data;

	if (!(new_data = ft_memalloc(sizeof(*new_data))))
		return (NULL);
	new_data->name_l = 0;
	new_data->column = 0;
	new_data->nb_exec = 0;
	new_data->start = 0;
	new_data->end = 0;
	new_data->nb_exec_sav = 0;
	new_data->type = 0;
	return (new_data);
}
