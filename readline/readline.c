/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 18:37:32 by yforeau          ###   ########.fr       */
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
		if (g_ctrl_mode)
			rl_ctrl_mode(c);
		else if (enter_rc(c) && !g_hist_lookup)
			return (g_vim_mode ? vim_insert() : rl_void());
		else
			readline_internal_test_cvalue(c);
		*value = g_line.line;
		if (g_input_break && g_subprompt)
			return ;
		insert_hist_compl();
		update_line();
		remove_hist_compl();
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

char		*readline_loop(const char *prompt, int *qmode)
{
	char	*value;
	char	*tmp;

	value = NULL;
	prep_terminal();
	initialize();
	set_prompt(prompt);
	rl_set_signals();
	value = readline_internal();
	deprep_terminal();
	rl_clear_signals();
	stack_delete(&g_back, del_stat_line);
	if (value != NULL)
		ft_putchar_fd('\n', STDERR_FILENO);
	if ((*qmode = get_str_qmode(*qmode, value)) & BSQUOTE)
		value[ft_strlen(value) - 1] = '\0';
	else
	{
		tmp = value;
		value = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	return (value);
}

char		*ft_readline(const char *prompt)
{
	char	*input;
	char	*compl;
	int		qmode;
	char	*new;

	input = NULL;
	qmode = NO_QUOTE;
	while (!input)
	{
		input = readline_loop(prompt, &qmode);
		while (qmode != NO_QUOTE)
		{
			qmode &= ~BSQUOTE;
			compl = readline_loop("> ", &qmode);
			new = ft_strjoin(input, compl);
			free(input);
			free(compl);
			input = new;
		}
		if (g_shell_is_interactive && input && input[0] && g_history && \
				(input = hist_expanse(input)))
			add_hentry(input, ft_strlen(input) - 1, 1);
	}
	if (g_verbose)
		ft_printf("%s\n", input);
	return (input);
}
