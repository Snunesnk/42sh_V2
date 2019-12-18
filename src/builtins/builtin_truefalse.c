/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_truefalse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/18 09:52:47 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtins.h"

int	cmd_true(int argc, t_process *p)
{
	(void)argc;
	(void)p;
	return (1);
}

int	cmd_false(int argc, t_process *p)
{
	(void)argc;
	(void)p;
	return (0);
}
