/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:54:51 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/01 16:49:33 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include <stdint.h>
# include <termcap.h>

# define RED_MASK	0xff0000
# define GREEN_MASK	0x00ff00
# define BLUE_MASK	0x0000ff

# define AM_INIT	1
# define AM_END		0

/*
** this is the length a pixel takes in frame_str
*/

# define COL_WIDTH	33

/*
**	height: height of the picture in characters (lines)
**	width: width of the picture in characters (columns)
**	frame_count: number of frames in the animation
**	pixel_count: height * width * frame_count
**
**	pixels: pixel representation of the animation by an
**	array of integers encoding rgb values in an hexadecimal
**	format (0xFF0000 is red for example, 0x00FF00 is green,
**	0xFFFFFF is white, etc...)
**	size: pixel_count
**
**	frame_str: string in which the frame to be printed will
**	be stored
**	size: pixel_count * (2 + len(escape_seq)) + height + 1
*/

typedef struct	s_anim
{
	uint64_t	height;
	uint64_t	width;
	uint64_t	frame_count;
	uint64_t	pixel_count;
	uint32_t	*pixels;
	char		*frame_str;
}				t_anim;

int				tputchar(int c);
int				anim_mode(int mode);
void			exec_animation(t_anim *anim);

#endif
