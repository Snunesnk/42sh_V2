/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:54:55 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/01 16:56:49 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h> //TODO: remove when ft_sprintf is added to libft
#include <string.h> //TODO: remove when libc functions are replaced
#include "libft.h"
#include "animation.h"

//TODO: replace libc functions

static int	msleep(uint32_t ms)
{
	struct timespec	ts;

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = ms * 1000 * 1000;
	return (nanosleep(&ts, NULL));
}

static void	load_line(t_anim *anim, uint64_t pix_i)
{
	uint64_t	r;
	uint64_t	g;
	uint64_t	b;
	uint64_t	col_i;
	char		str[COL_WIDTH + 1];

	col_i = 0;
	while (col_i < anim->width)
	{
		r = (anim->pixels[pix_i + col_i] & RED_MASK) >> 16;
		g = (anim->pixels[pix_i + col_i] & GREEN_MASK) >> 8;
		b = anim->pixels[pix_i + col_i] & BLUE_MASK;
		sprintf(str, "\e[0;38;2;%03lu;%03lu;%03lum▇▇", r, g, b); //TODO: ADD TO LIBFT
		strcat(anim->frame_str, str);
		++col_i;
	}
	strcat(anim->frame_str, "\n");
}

void		exec_animation(t_anim *anim)
{
	char		*cl;
	uint64_t	pix_i;
	uint64_t	line_i;

	cl = tgetstr("cl", NULL);
	pix_i = 0;
	line_i = 0;
	while (pix_i < anim->pixel_count)
	{
		tputs(cl, 1, tputchar);
		line_i = 0;
		memset((void *)anim->frame_str, 0, sizeof(anim->frame_str));
		while (line_i < anim->height)
		{
			load_line(anim, pix_i);
			pix_i += anim->width;
			++line_i;
		}
		printf(anim->frame_str);
		msleep(65);
	}
	printf("\e[m");
}
