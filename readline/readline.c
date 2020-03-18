/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 18:07:38 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	g_hist_lookup = 0;

static void	readline_internal_keys(union u_buffer c, char **value)
{
	while (c.value)
	{
		if (g_input_break)
			return (g_vim_mode ? vim_insert() : rl_void());
		c = read_key();
//		ft_printf("\n%d %d %d %d %d %d %d\n", (int)c.buf[0], (int)c.buf[1], (int)c.buf[2], (int)c.buf[3], (int)c.buf[4], (int)c.buf[5], (int)c.buf[6]);
		if (!g_ctrl_mode && g_hist_lookup)
			hist_lookup(c);
		if (g_ctrl_mode)
			rl_ctrl_mode(c);
		else if (enter_rc(c))
			return (g_vim_mode ? vim_insert() : rl_void());
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
		*value = g_line.line;
	}
}

static char	*readline_internal(void)
{
	char			*value;

	value = NULL;
	init_line_buffer();
	value = g_line.line;
	update_line();
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
	while (!value)
	{
		value = readline_internal();
		if (value && value[0] && (value = hist_expanse(value)))
		{
			add_hentry(value, 1);
			break ;
		}
	}
	deprep_terminal();
	rl_clear_signals();
	if (value != NULL)
		ft_putchar_fd('\n', 2);
	return (value);
}

char		*ft_readline(const char *prompt)
{
	char	*input;
	char	*compl;
	char	*new;

	input = readline_loop(prompt);
	while (is_quote_open(input))
	{
		compl = readline_loop("> ");
		new = ft_strjoin(input, compl);
		free(input);
		free(compl);
		input = new;
	}
	return (input);
}
