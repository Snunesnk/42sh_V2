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

/* Block terminal generated signals, save old mask and set shell one */
void	init_shell_sset(void)
{
	sigset_t	newmask;

	/* Blocking signals terminal generated signals */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&newmask, SIGQUIT);
	sigaddset(&newmask, SIGTSTP);
	sigaddset(&newmask, SIGTTIN);
	sigaddset(&newmask, SIGTTOU);
	if (sigprocmask(SIG_BLOCK, &newmask, &g_save_procmask))
		exit(1);
	/* SIGCHLD set */
//	sigemptyset(&g_shell_sset.sa_mask);
//	sigaddset(&g_shell_sset.sa_mask, SIGINT);
//	sigaddset(&g_shell_sset.sa_mask, SIGQUIT);
//	sigaddset(&g_shell_sset.sa_mask, SIGTSTP);
//	sigaddset(&g_shell_sset.sa_mask, SIGTTIN);
//	sigaddset(&g_shell_sset.sa_mask, SIGTTOU);
//	sigaddset(&g_shell_sset.sa_mask, SIGCHLD);
//	g_shell_sset.sa_flags = SA_SIGINFO | SA_RESTART;
//	g_shell_sset.sa_sigaction = handle_chld; /* Update child status handler, function */
//	sigaction(SIGCHLD, &g_shell_sset, NULL);
}

/* Restore proc mask inheritated from shell starting proc*/
void	restore_procmask(void)
{
	if (sigprocmask(SIG_SETMASK, &g_save_procmask, NULL))
		exit(1);
}
