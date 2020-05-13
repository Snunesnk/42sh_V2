/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:17:06 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/13 17:17:08 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main_error(int status, t_list *lst)
{
	g_retval = status;
	if (!g_shell_is_interactive && status == 2)
		exit_clean(2);
	do_job_notification(g_first_job, NULL, NULL);
	free_lst(lst);
	return (g_retval);
}
