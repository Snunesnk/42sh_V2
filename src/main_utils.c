/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:10:03 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/13 17:12:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parse_error(int status, t_list *lst)
{
	g_retval = status;
	if (!g_shell_is_interactive && status == 2)
		exit_clean(2);
	do_job_notification(g_first_job, NULL, NULL);
	free_lst(lst);
	return (g_retval);
}
