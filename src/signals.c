#include "shell.h"

sigset_t		g_save_procmask;

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
	sigaddset(&newmask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &newmask, &g_save_procmask))
		exit(1); /* Clean exit, free mem */
}

/* Restore proc mask inheritated from shell starting proc*/
void	restore_procmask(void)
{
	if (sigprocmask(SIG_SETMASK, &g_save_procmask, NULL))
		exit(1);
}
