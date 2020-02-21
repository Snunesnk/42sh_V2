#include "shell.h"

struct sigaction g_shell_sset;

void	init_shell_sset(void)
{
	if (sigemptyset(&g_shell_sset.sa_mask))
		exit(1);
	if (sigaddset(&g_shell_sset.sa_mask, SIGINT)
		|| sigaddset(&g_shell_sset.sa_mask, SIGQUIT)
		|| sigaddset(&g_shell_sset.sa_mask, SIGTSTP)
		|| sigaddset(&g_shell_sset.sa_mask, SIGTTIN)
		|| sigaddset(&g_shell_sset.sa_mask, SIGTTOU)
		|| sigaddset(&g_shell_sset.sa_mask, SIGCHLD))
		exit(1);
	g_shell_sset.sa_handler = (void (*)(int))update_status; /* Update child status handler, function */
	g_shell_sset.sa_flags = 0;
}
