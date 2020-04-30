/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getch_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:36:04 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/30 11:09:29 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_getch_fd(int fd)
{
	int	ch;

	if ((int)read(fd, (void*)&ch, sizeof(char)) <= 0)
	{
		return (-1);
	}
	else
	{
		return (ch);
	}
}
