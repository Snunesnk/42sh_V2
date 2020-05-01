/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_monkey.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 15:53:55 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/01 16:58:02 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"

extern t_anim	g_monkey;

int				cmd_monkey(int argc, char **argv)
{
	int		do_the_monkey;

	(void)argc;
	(void)argv;
	if (anim_mode(AM_INIT) == -1)
		return (1);
	do_the_monkey = 2;
	while (do_the_monkey)
	{
		exec_animation(&g_monkey);
		--do_the_monkey;
	}
	anim_mode(AM_END);
	return (0);
}
