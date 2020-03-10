/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:18 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 12:27:01 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

struct s_quote	g_quote =
{
	.c = 0,
	.no_quote_prompt = "> ",
	.no_quote_prompt_len = 2,
	.handle = 1,
};

int		is_quote_open(const char *s)
{
	if (g_quote.handle != 1)
		return (0);
	while (*s)
	{
		if (*s == '\\')
		{
			++s;
			if (*s == '\0')
			{
				g_quote.c = 1;
				break ;
			}
		}
		else if (g_quote.c == 0 && (*s == '\"' || *s == '\'' || *s == '`'))
			g_quote.c = *s;
		else if (*s && *s == g_quote.c)
			g_quote.c = 0;
		++s;
	}
	if (g_quote.c)
		return ((g_quote.c = 0) || 1);
	else
		return (0);
}
