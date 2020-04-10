/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 14:28:32 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 14:39:35 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

/*
** Return 1 if index is without quotes or has \ before, i.e. inihibited
*/

char	*move_to_next_inhibitor_boundary(char *s)
{
	char	backq;
	size_t	i;

	i = 0;
	baskq = 0;
	while (s[i] && i < index)
	{
		if (s[i] == '\'')
			backq ^= '\'';
	}
	return (backq);
}
