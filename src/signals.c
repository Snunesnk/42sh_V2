#include "shell.h"

sigset_t		g_save_procmask;
struct sigaction	g_shell_sset;

void	handle_chld(int signo, siginfo_t *info, void *context)
{
	(void)signo;
	(void)context;
	ft_printf("\nsending pid:%d\n", info->si_pid);
	update_status();
}

void	init_shell_sset(void)
{
	if (sigprocmask(SIG_UNBLOCK, NULL, &g_save_procmask))
		exit(1);
	if (sigemptyset(&g_shell_sset.sa_mask))
		exit(1);
	if (sigaddset(&g_shell_sset.sa_mask, SIGINT)
		|| sigaddset(&g_shell_sset.sa_mask, SIGQUIT)
		|| sigaddset(&g_shell_sset.sa_mask, SIGTSTP)
		|| sigaddset(&g_shell_sset.sa_mask, SIGTTIN)
		|| sigaddset(&g_shell_sset.sa_mask, SIGTTOU)
		|| sigaddset(&g_shell_sset.sa_mask, SIGCHLD))
		exit(1);
	g_shell_sset.sa_flags = SA_SIGINFO | SA_RESTART;
	g_shell_sset.sa_sigaction = handle_chld; /* Update child status handler, function */
}
