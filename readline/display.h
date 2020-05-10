/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:46 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/09 23:42:41 by snunes           ###   ########.fr       */
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
	int		start_offset;
	int		start_line;
};

struct	s_line_state
{
	char		*line;
	int			size_buf;
	int			c_pos;
	int			cursor_pos;
	int			len;
	char		is_modified;
};

extern struct s_line_state	g_line;
extern struct s_display		g_dis;

void	set_prompt(const char *prompt);
void	display_prompt(void);
void	update_line(void);
void	redisplay_after_sigwinch(void);
void	init_line_buffer(void);
void	get_cursor_position(int *row, int *col);
void	place_cursor(int pos);
void	calc_dcursor(int pos, int *v_pos, int *c_pos);
void	update_dumb_line(void);
void	clear_next(void);

#endif
