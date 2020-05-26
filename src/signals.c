/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:14:15 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/26 15:37:11 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

sigset_t		g_save_procmask;

static const t_signal	g_signalstr[] =
{
	{ SIGHUP, "SIGHUP" },
	{ SIGINT, "SIGINT" },
	{ SIGQUIT, "SIGQUIT" },
	{ SIGILL, "SIGILL" },
	{ SIGABRT, "SIGABRT" },
	{ SIGFPE, "SIGFPE" },
	{ SIGKILL, "SIGKILL" },
	{ SIGSEGV, "SIGSEGV" },
	{ SIGPIPE, "SIGPIPE" },
	{ SIGALRM, "SIGALRM" },
	{ SIGTERM, "SIGTERM" },
	{ SIGUSR1, "SIGUSR1" },
	{ SIGUSR2, "SIGUSR2" },
	{ SIGCHLD, "SIGCHLD" },
	{ SIGCONT, "SIGCONT" },
	{ SIGSTOP, "SIGSTOP" },
	{ SIGTSTP, "SIGTSTP" },
	{ SIGTTIN, "SIGTTIN" },
	{ SIGTTOU, "SIGTTOU" },
	{ 0, NULL }
};

void			init_shell_sset(void)
{
	sigset_t		newmask;

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIGQUIT);
	sigaddset(&newmask, SIGTSTP);
	sigaddset(&newmask, SIGTTIN);
	sigaddset(&newmask, SIGTTOU);
	sigaddset(&newmask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &newmask, &g_save_procmask))
		exit_clean(2);
}

void			restore_procmask(void)
{
	if (sigprocmask(SIG_SETMASK, &g_save_procmask, NULL))
		exit_clean(2);
}

const char		*strsig(int sig)
{
	int	i;

	i = 0;
	while (g_signalstr[i].str)
	{
		if (g_signalstr[i].sig == sig)
			return (g_signalstr[i].str);
		++i;
	}
	return (NULL);
}

void			display_sigmsg(int sig)
{
	if (sig == SIGHUP)
		ft_dprintf(STDERR_FILENO, "Hangup\n");
	else if (sig == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit\n");
	else if (sig == SIGILL)
		ft_dprintf(STDERR_FILENO, "Illegal instruction\n");
	else if (sig == SIGABRT)
		ft_dprintf(STDERR_FILENO, "Aborted\n");
	else if (sig == SIGFPE)
		ft_dprintf(STDERR_FILENO, "Floating point exception\n");
	else if (sig == SIGKILL)
		ft_dprintf(STDERR_FILENO, "Killed\n");
	else if (sig == SIGBUS)
		ft_dprintf(STDERR_FILENO, "Bus error\n");
	else if (sig == SIGTRAP)
		ft_dprintf(STDERR_FILENO, "Trace/breakpoint trap\n");
	else if (sig == SIGALRM)
		ft_dprintf(STDERR_FILENO, "Alarm clock\n");
	else if (sig == SIGTERM)
		ft_dprintf(STDERR_FILENO, "Terminated\n");
	else if (sig == SIGUSR1)
		ft_dprintf(STDERR_FILENO, "User defined signal 1\n");
	else
		display_sigmsg2(sig);
}

void			display_sigmsg2(int sig)
{
	if (sig == SIGPOLL)
		ft_dprintf(STDERR_FILENO, "I/O possible\n");
	else if (sig == SIGUSR2)
		ft_dprintf(STDERR_FILENO, "User defined signal 2\n");
	else if (sig == SIGPROF)
		ft_dprintf(STDERR_FILENO, "Profiling timer expired\n");
	else if (sig == SIGSYS)
		ft_dprintf(STDERR_FILENO, "Bad system call\n");
	else if (sig == SIGVTALRM)
		ft_dprintf(STDERR_FILENO, "Virtual timer expired\n");
	else if (sig == SIGXCPU)
		ft_dprintf(STDERR_FILENO, "CPU time limit exceeded\n");
	else if (sig == SIGXFSZ)
		ft_dprintf(STDERR_FILENO, "File size limit exceeded\n");
}
