/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 10:23:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/18 15:54:35 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtins.h"

int	cmd_fg(int argc, t_process *p)
{
	extern t_job	*first_job;

	(void)argc;
	(void)p;
	continue_job(first_job, 1);
	return (0);
}
