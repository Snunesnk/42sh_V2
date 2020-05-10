/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:14:15 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 10:55:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			g_interrupt_immediately = 0;
sigset_t		g_save_procmask;
struct sigaction	g_sigint_oact;
struct sigaction	g_sigint_act;

static void	sigint_handler(int sig)
{
	g_interrupt_immediately = sig;
	g_retval = sig + 128;
//	write(STDOUT_FILENO, "^C", 2); // Should ask readline to ouput ^C
	/* Case readline ON */
//	ft_printf("\n\nHello SIGINT: %d\n\n", sig);
//	kill(getpid(), sig);
}

void	init_shell_sset(void)
{
	sigset_t		newmask;
	sigset_t		sigint_mask;

	/* Other SIG */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	sigaddset(&newmask, SIGTSTP);
	sigaddset(&newmask, SIGTTIN);
	sigaddset(&newmask, SIGTTOU);
	sigaddset(&newmask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &newmask, &g_save_procmask))
		exit_clean(2);

	/* SIGINT */
	sigemptyset(&sigint_mask);
//	sigaddset(&sigint_mask, SIGINT);
	g_sigint_act.sa_handler = sigint_handler; // Set sigint handler
	g_sigint_act.sa_mask = sigint_mask; // Block sigint during sigint handler execution
	g_sigint_act.sa_flags = 0; // Sigcall not auto restarted
	if (sigaction(SIGINT, &g_sigint_act, &g_sigint_oact))
		exit_clean(2);

}

void	restore_procmask(void)
{
	if (sigprocmask(SIG_SETMASK, &g_save_procmask, NULL))
		exit_clean(2);
	if (sigaction(SIGINT, &g_sigint_oact, &g_sigint_act))
		exit_clean(2);
}

static const t_signal	signalstr[] =
{
	{ SIGHUP , "SIGHUP" },
	{ SIGINT , "SIGINT" },
	{ SIGQUIT , "SIGQUIT" },
	{ SIGILL , "SIGILL" },
	{ SIGABRT , "SIGABRT" },
	{ SIGFPE , "SIGFPE" },
	{ SIGKILL , "SIGKILL" },
	{ SIGSEGV , "SIGSEGV" },
	{ SIGPIPE , "SIGPIPE" },
	{ SIGALRM , "SIGALRM" },
	{ SIGTERM , "SIGTERM" },
	{ SIGUSR1 , "SIGUSR1" },
	{ SIGUSR2 , "SIGUSR2" },
	{ SIGCHLD , "SIGCHLD" },
	{ SIGCONT , "SIGCONT" },
	{ SIGSTOP , "SIGSTOP" },
	{ SIGTSTP , "SIGTSTP" },
	{ SIGTTIN , "SIGTTIN" },
	{ SIGTTOU , "SIGTTOU" },
	{ 0 , NULL }
};

const char	*strsig(int sig)
{
	int	i;

	i = 0;
	while (signalstr[i].str)
	{
		if (signalstr[i].sig == sig)
			return (signalstr[i].str);
		++i;
	}
	return (NULL);
}
