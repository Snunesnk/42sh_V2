/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/03 17:22:45 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct sigaction	g_sigact_winch = {0};
struct sigaction	g_dummy_winch = {0};

void	rl_set_signals(void)
{
	if (g_sigact_winch.sa_handler == NULL)
	{
		sigemptyset(&g_sigact_winch.sa_mask);
		sigaddset(&g_sigact_winch.sa_mask, SIGWINCH);
		g_sigact_winch.sa_flags = SA_RESTART;
		g_sigact_winch.sa_handler = resize_terminal;
	}
	sigaction(SIGWINCH, &g_sigact_winch, &g_dummy_winch);
}

void	rl_clear_signals(void)
{
	sigaction(SIGWINCH, &g_dummy_winch, NULL);
}
