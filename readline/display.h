/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:46 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 20:20:08 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

struct	s_display
{
	char	*prompt;
	char	*display_prompt;
	int		prompt_l;
	int		real_prompt_l;
	int		botl;
	int		cbpos;
	int		cbpos_prev;
	int		line_size;
	int		fst_line_l;
	int		start_offset;
	int		start_line;
};

struct	s_line_state
{
	char	*line;
	int		size_buf;
	int		len;
};

struct	s_cursor
{
	int	c_pos;
	int	v_pos;
};

extern struct s_line_state	g_line;

extern struct s_display		g_dis;
extern struct s_cursor		g_cursor;

void	set_prompt(const char *prompt);
void	display_prompt(void);
void	update_line(void);
void	redisplay_after_sigwinch(void);
void	init_line_buffer(void);
void	get_start_offset(void);
void	count_newline(void);

#endif
