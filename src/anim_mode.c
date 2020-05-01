/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 16:15:06 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/01 16:30:38 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "animation.h"

int		tputchar(int c)
{
	return (write(1, &c, 1));
}

int		anim_mode(int mode)
{
	char	*t;
	char	*v;

	t = NULL;
	v = NULL;
	if (mode == AM_INIT)
	{
		t = tgetstr("ti", NULL);
		v = tgetstr("vi", NULL);
	}
	else if (mode == AM_END)
	{
		t = tgetstr("te", NULL);
		v = tgetstr("ve", NULL);
	}
	if (!t || !v)
		return (-1);
	tputs(t, 1, tputchar);
	tputs(v, 1, tputchar);
	return (0);
}
