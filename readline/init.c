/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:21:50 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 15:40:57 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	initialize(void)
{
	static int	initialized;

	if (initialized == 0)
	{
		if (g_term.terminal_name == NULL)
			g_term.terminal_name = ft_getenv("TERM");
		tgetent(NULL, g_term.terminal_name);
		init_terminal();
		++initialized;
	}
}
