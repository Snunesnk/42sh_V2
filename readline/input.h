/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:01 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 12:08:07 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

int						g_add_back_buf;
extern struct s_stack	*g_back;

union					u_buffer
{
	unsigned long	value;
	char			buf[sizeof(unsigned long)];
};

struct					s_quote
{
	char	c;
	char	*no_quote_prompt;
	int		no_quote_prompt_len;
	int		handle;
};

extern struct s_quote	g_quote;
extern _Bool			g_input_break;
extern _Bool			g_subprompt;
extern _Bool			g_eof;

union u_buffer			read_key(void);
int						is_quote_open(char *s);
void					del_stat_line(void *ptr);

#endif
