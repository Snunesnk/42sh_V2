/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:21:56 by abarthel          #+#    #+#             */
/*   Updated: 2020/06/12 16:23:28 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "builtins.h"

_Bool			g_input_break = 0;
_Bool			g_subprompt = 0;
_Bool			g_eof = 0;
int				g_add_back_buf;
struct s_stack	*g_back;

union u_buffer	read_key(void)
{
	union u_buffer	buffer_u;
	int				status;

	buffer_u.value = 0;
	while ((status = read(STDIN_FILENO, buffer_u.buf, \
					sizeof(buffer_u.buf)) < 0))
		continue ;
	return (buffer_u);
}

void			del_stat_line(void *ptr)
{
	struct s_line_state	*prev;

	prev = ptr;
	free(prev->line);
	free(prev);
}
