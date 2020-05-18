/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:20:25 by snunes            #+#    #+#             */
/*   Updated: 2020/05/18 13:40:20 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	fill_line(char *hist_proposal, int mode)
{
	int	hist_len;

	hist_len = ft_strlen(hist_proposal);
	if (mode == 1)
	{
		insert_text("' : ", 4);
		insert_text(hist_proposal, hist_len);
		update_line();
		g_line.c_pos -= hist_len;
	}
	else
	{
		clear_line();
		insert_text(hist_proposal, hist_len);
	}
}

static void	get_input_proposal(char value, char **hist_proposal)
{
	char	*user_input;

	g_line.c_pos -= 4;
	if (ft_isprint(value))
		insert_text((char *)&value, 1);
	else if (value == 127)
		rl_backspace();
	g_line.line[g_line.c_pos] = '\0';
	user_input = g_line.line;
	*hist_proposal = g_hist.history_content + g_hist.offset + 1;
	if (!(get_matching_hist(hist_proposal, user_input)))
		set_prompt("(failed reverse-i-search)`");
	else if (ft_strequ(g_dis.prompt, "(failed reverse-i-search)`"))
		set_prompt("(reverse-i-search)`");
	ft_putstr(tgoto(g_termcaps.cm, 0, g_dis.start_line));
	display_prompt();
	g_line.len = ft_strlen(user_input);
	ft_bzero(g_line.line + g_line.len, g_line.size_buf - g_line.len);
	g_line.cursor_pos = 0;
}

static void	prepare_hist_lookup(char **original_prompt)
{
	if (!(*original_prompt = ft_strdup(g_dis.prompt)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return ;
	}
	g_hist_lookup = 1;
	set_prompt("(reverse-i-search)`");
	ft_putstr(tgoto(g_termcaps.cm, 0, g_dis.start_line));
	display_prompt();
	g_line.c_pos = 0;
	insert_text("' : ", 4);
	g_line.cursor_pos = 0;
}

/*
** This is the main function.
** First, it looks for the value of g_hist_lookup. If g_hist_lookup == 0, then
** this is the first time hist_lookup is called, therefor the prompt needs to
** be replaced by a new one: (reverse i-search)`, and the old one is saved in
** the static original_prompt.
** Then it set the value of g_hist_lookup to 1, and set the content of g_line
** as hist proposal following this pattern: [user_input]' : [hist_proposal].
**
** Then, if this is the second time or more hist_lookup is called, add the
** given char to [user_input] if it's a printable one, or delete the last one
** if it correspond to backspace key.
** Now, a new hist_proposal needs to be found according to this new user input,
** and it is performed by get_matching_hist.
**
** Two cases now : if the user_input is not handle by history_lookup, set the
** original_prompt back, set g_hist_lookup to 0 to not enter this function
** until CTRL-R is pressed again, and set g_line with the last input proposal.
**
** Else, just erase the last hist_proposal from g_line, and adds the new one.
** Then wait for readline to read another char and send it to hist_lookup.
*/

void		hist_lookup(union u_buffer c)
{
	static char	*original_prompt = NULL;
	char		*hist_proposal;

	hist_proposal = NULL;
	if (!g_hist_lookup)
	{
		prepare_hist_lookup(&original_prompt);
		return ;
	}
	get_input_proposal(c.value, &hist_proposal);
	if (!isprintchr(c.value) && c.value != 127)
	{
		set_prompt(original_prompt);
		free(original_prompt);
		original_prompt = NULL;
		g_hist_lookup = 0;
		ft_putstr(tgoto(g_termcaps.cm, 0, g_dis.start_line));
		display_prompt();
		g_dis.start_offset = g_dis.prompt_l;
		fill_line(hist_proposal, 0);
		g_bad_seq.value = c.value;
		return ;
	}
	fill_line(hist_proposal, 1);
}
