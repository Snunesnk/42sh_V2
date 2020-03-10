/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:01 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 12:23:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

union	u_buffer
{
	unsigned long	value;
	char			buf[sizeof(unsigned long)];
};

struct	s_quote
{
	char	c;
	char	*no_quote_prompt;
	int		no_quote_prompt_len;
	int		handle;
};

extern struct s_quote	g_quote;

union u_buffer	read_key(void);
int				is_quote_open(const char *s);

#endif
