/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 13:37:18 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/09 13:37:43 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int	check_two_words(int s)
{
	int		start;
	_Bool	a;
	_Bool	b;

	a = 0;
	b = 0;
	start = s;
	while (start && g_line.line[start - 1] == ' ')
		--start;
	while (start && g_line.line[start - 1] != ' ')
	{
		a |= 1;
		--start;
	}
	while (start && g_line.line[start - 1] == ' ')
		--start;
	while (start && g_line.line[start - 1] != ' ')
	{
		b |= 1;
		--start;
	}
	if (a && b)
		return (1);
	return (0);
}

static char	*get_pword(void)
{
	int		start;
	int		len;
	char	*w;

	start = g_dis.cbpos;
	while (start && g_line.line[start - 1] == ' ')
		--start;
	while (start && g_line.line[start - 1] != ' ')
		--start;
	len = g_dis.cbpos - start;
	w = ft_strndup(&(g_line.line[start]), len);
	ft_memmove(&(g_line.line[start]),
	&(g_line.line[g_dis.cbpos]), g_line.len - g_dis.cbpos);
	g_line.len -= len;
	ft_bzero(&(g_line.line[g_line.len]), len);
	g_dis.cbpos = start;
	return (w);
}

static int	get_ew2(void)
{
	int	endo;
	int	endt;

	endo = g_dis.cbpos;
	while (g_line.line[endo] && g_line.line[endo] == ' ')
		endo++;
	while (g_line.line[endo] && g_line.line[endo] != ' ')
		endo++;
	endt = endo;
	while (g_line.line[endt] && g_line.line[endt] == ' ')
		endt++;
	if (!g_line.line[endt])
		return (endt);
	else if (g_line.line[endt] != ' ')
		return (endo);
	return (0);
}

void		swap_words(void)
{
	int		spaces;
	int		ew2;
	char	*w1;
	char	*w2;

	spaces = 0;
	ew2 = get_ew2();
	if (ew2 && check_two_words(ew2))
	{
		g_dis.cbpos = ew2;
		w2 = get_pword();
		while (g_line.line[g_dis.cbpos - 1] == ' ')
		{
			++spaces;
			--g_dis.cbpos;
		}
		w1 = get_pword();
		insert_text(w2, ft_strlen(w2));
		g_dis.cbpos += spaces;
		insert_text(w1, ft_strlen(w1));
		update_line();
		free(w1);
		free(w2);
	}
}
