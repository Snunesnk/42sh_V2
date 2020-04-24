/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/24 15:45:36 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "builtins.h"

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
		if (g_ctrl_mode)
			rl_ctrl_mode(c);
		else if (enter_rc(c) && !g_hist_lookup)
			return (g_vim_mode ? vim_insert() : rl_void());
		else
			readline_internal_test_cvalue(c);
		*value = g_line.line;
		update_line();
	}
}

static char	*readline_internal(void)
{
	char			*value;

	value = NULL;
	init_line_buffer();
	value = g_line.line;
	if (g_shell_is_interactive)
		get_start_offset();
	else
		g_dis.start_offset = 0;
	update_line();
	if (g_vim_mode == 0)
		add_back();
	readline_internal_keys((union u_buffer){.value = 1}, &value);
	return (value);
}

char		*readline_loop(const char *prompt)
{
	char	*value;

	value = NULL;
	prep_terminal();
	if (!g_hist)
		init_history();
	initialize();
	set_prompt(prompt);
	rl_set_signals();
	value = readline_internal();
	deprep_terminal();
	rl_clear_signals();
	stack_delete(&g_back, del_stat_line);
	if (value != NULL)
		ft_putchar_fd('\n', 2);
	return (value);
}

char		*ft_readline(const char *prompt)
{
	char	*input;
	char	*compl;
	char	*new;

	input = NULL;
	while (!input)
	{
		input = readline_loop(prompt);
		while (is_quote_open(input))
		{
			compl = readline_loop("> ");
			new = ft_strjoin(input, compl);
			free(input);
			free(compl);
			input = new;
		}
		if (g_shell_is_interactive && input && input[0] && g_history && \
				(input = hist_expanse(input)))
			add_hentry(input, ft_strlen(input), 1);
	}
	if (g_verbose)
		ft_printf("%s\n", input);
	return (input);
}
