/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:09 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 12:19:53 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# define READLINE_DEFAULT_BUFFER_SIZE 256

struct	s_line
{
	char	*buffer;
	size_t	len;
};

void	init_line_buffer(void);

struct	s_clipboard
{
	char	*str;
	int		l;
};

extern struct s_clipboard	g_clip;

#endif
