/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 10:23:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/18 10:44:37 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "job_control.h"


int	cmd_fg(int argc, t_process *p)
{
	extern t_job	*first_job;

	(void)argc;
	(void)p;
	continue_job(first_job, 1);
	return (0);
}
