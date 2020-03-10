/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc_hist_num.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:41:25 by snunes            #+#    #+#             */
/*   Updated: 2020/03/10 22:20:21 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			get_alpha_value(char *args)
{
	char	*tmp;
	int		hist_num;

	tmp = prev_hist();
	if (!(get_beg_matching_hist(&tmp, args)))
		hist_num = -1;
	else
		hist_num = g_hist->nb_line;
	while (g_hist->nb_line != g_hist->total_lines)
		next_hist();
	return (hist_num);
}

int			get_numeric_value(char *args)
{
	int hist_num;

	hist_num = ft_atoi(args);
	if (hist_num < 0)
	{
		hist_num -= 1;
		hist_num = g_hist->total_lines + hist_num;
	}
	return (hist_num);
}

void		swap_entries(int *hist_end, int *hist_beg)
{
	int	tmp;

	tmp = *hist_end;
	*hist_end = *hist_beg;
	*hist_beg = tmp;
}

void		get_hist_num(char **args, int opt_list, int *hist_end, \
		int *hist_beg)
{
	if (ft_str_is_numeric(*args) || (**args == '-' \
				&& ft_str_is_numeric(*args + 1)))
		*hist_beg = get_numeric_value(*args);
	else
		*hist_beg = get_alpha_value(*args);
	args += 1;
	if (!*args)
	{
		*hist_end = (opt_list & FC_L_OPTION) ? g_hist->total_lines - 1 \
					: *hist_beg;
		return ;
	}
	if (ft_str_is_numeric(*args) || (**args == '-' \
				&& ft_str_is_numeric(*args + 1)))
		*hist_end = get_numeric_value(*args);
	else
		*hist_end = get_alpha_value(*args);
	if (*hist_end < *hist_beg)
		swap_entries(hist_end, hist_beg);
}
