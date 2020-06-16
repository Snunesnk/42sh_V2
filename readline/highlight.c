/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   highlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 16:06:00 by snunes            #+#    #+#             */
/*   Updated: 2020/06/14 19:02:47 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

/*
** Ok donc en fait tout se joue à l'index 5, qui est égal à :
** - 68 pour flèche gauche
** - 67 pour flèche droite
** - 65 pour flèche du haut
** - 66 pour flèche du bas
** Je ne vais utiliser que droite et gauche. Il va falloir que je compte les chars à colorer, pour les colorer justement.
** Avec ça, si je choppe un echap, j'efface tout et je quitte
** Si je choppe un char que je peux print, je remplace toute la sélection par ce char, et si j'était e mode cmd sur vim j'entre en mode insert
** Si je choppe un suppr ou un backspace, alors j'efface tout
** Si je récupère une séquence non-printable, alors je place la séléction dans g_clip.str.
*/
void	highlight(union u_buffer c)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		printf("c.buf[%d]: %d\n", i, c.buf[i]);
		i++;
	}
	sleep(1);
}
