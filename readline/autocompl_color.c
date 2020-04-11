/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 21:55:19 by snunes            #+#    #+#             */
/*   Updated: 2020/04/11 21:58:30 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "sys/types.h"
#include "sys/stat.h"

static char	*get_sp_color(struct stat st)
{
	static char	*(color[6]) = {"\033[01;32m", "\033[1;34m", "\033[37;41m", \
		"\033[30;43m", "\033[30;42m", "\033[34;42m"};

	if (S_IFDIR & st.st_mode)
	{
		if (S_IWOTH & st.st_mode && 000100 & st.st_mode)
			return (color[4]);
		else if (S_IWOTH & st.st_mode)
			return (color[5]);
		return (color[1]);
	}
	if (S_ISUID & st.st_mode)
		return (color[2]);
	if (S_ISGID & st.st_mode)
		return (color[3]);
	return (color[0]);
}

char		*get_color(char *file)
{
	static char	*(color[8]) = {"\033[37m", "\033[40;33;01m", \
		"\033[40;33;01m", "\033[40;33m", "\033[1;36m", "\033[1;35m"};
	struct stat	st;

	lstat(file, &st);
	if (S_ISDIR(st.st_mode))
		return (get_sp_color(st));
	if (S_ISCHR(st.st_mode))
		return (color[1]);
	if (S_ISBLK(st.st_mode))
		return (color[2]);
	if (S_ISFIFO(st.st_mode))
		return (color[3]);
	if (S_ISLNK(st.st_mode))
		return (color[4]);
	if (S_ISSOCK(st.st_mode))
		return (color[5]);
	if (S_ISREG(st.st_mode))
	{
		if (is_exec(file))
			return (get_sp_color(st));
		return (color[0]);
	}
	return (color[0]);
}
