/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 16:55:51 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "builtins.h"
#include "quotes.h"

int	g_hist_lookup = 0;

static void	readline_internal_test_cvalue(union u_buffer c)
{

	if (!g_ctrl_mode && g_hist_lookup)
		hist_lookup(c);
	else if (isstdkey(c.value))
		(g_standard_keymap[c.value].func)(c.value);
	else if (isctrlkey(c))
	{
		if (mvctrlkey(c))
			c.buf[2] = c.buf[5] + 20;
		(g_ctlx_keymap[(int)c.buf[2]].func)();
	}
	else if (ismetachar(c))
		(g_meta_keymap[(int)c.buf[1]].func)();
	else
		paste_via_input(c.value);
}

static void	readline_internal_keys(union u_buffer c, char **value)
{
	while (c.value)
	{
		if (g_input_break)
			return (g_vim_mode ? vim_insert() : rl_void());
		if (g_bad_seq.value != 0)
		{
			c = g_bad_seq;
			g_bad_seq.value = 0;
		}
		else
			c = read_key();
		c = get_vim_cmd_count(c);
		if (g_ctrl_mode)
			rl_ctrl_mode(c);
		else if (enter_rc(c) && !g_hist_lookup)
			return (g_vim_mode ? vim_insert() : rl_void());
		else
			readline_internal_test_cvalue(c);
		*value = g_line.line;
		if (g_input_break && g_subprompt)
			return ;
		update_line();
		if (g_line.len)
			print_hist_compl();
	}
}

static char	*readline_internal(void)
{
	char			*value;

	value = NULL;
	init_line_buffer();
	value = g_line.line;
	update_line();
	if (g_back)
		stack_delete(&g_back, del_stat_line);
	readline_internal_keys((union u_buffer){.value = 1}, &value);
	remove_completion();
	ft_putstr_fd(g_termcaps.cd, g_dis.fd);
	return (value);
}

char		*ft_readline(char *prompt)
{
	char	*input;

	prep_terminal();
	initialize();
	rl_set_signals();
	prompt = !prompt ? get_prompt() : ft_strdup(prompt);
	set_prompt(prompt);
	free(prompt);
	display_prompt();
	input = NULL;
	input = readline_internal();
	input = hist_expanse(input);
	deprep_terminal();
	rl_clear_signals();
	if (g_input_break)
		ft_putchar_fd('\r', g_dis.fd);
	else if (input)
		ft_putchar_fd('\n', g_dis.fd);
	if (g_verbose)
		ft_dprintf(g_dis.fd, "%s\n", input);
	return (input);
}
