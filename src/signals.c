/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:14:15 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/28 12:42:20 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

sigset_t		g_save_procmask;

void	init_shell_sset(void)
{
	sigset_t	newmask;

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIGQUIT);
	sigaddset(&newmask, SIGTSTP);
	sigaddset(&newmask, SIGTTIN);
	sigaddset(&newmask, SIGTTOU);
	sigaddset(&newmask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &newmask, &g_save_procmask))
		exit_clean(1);
}

void	restore_procmask(void)
{
	if (sigprocmask(SIG_SETMASK, &g_save_procmask, NULL))
		exit_clean(1);
}
