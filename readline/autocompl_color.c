/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 21:55:19 by snunes            #+#    #+#             */
/*   Updated: 2020/05/22 14:50:38 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "error.h"

char		*remove_esc(char *file)
{
	char	*no_esc_file;
	int		i;

	i = 0;
	if (!(no_esc_file = ft_strdup(file)))
	{
		psherror(e_cannot_allocate_memory, g_progname, e_cmd_type);
		return (NULL);
	}
	ft_bzero(no_esc_file, ft_strlen(file));
	while (file[i])
	{
		if (file[i] == '\\' && ft_strchr(SHELL_SPECIAL_CHARS, file[i + 1]))
			i++;
		ft_strncat(no_esc_file, file + i, 1);
		i++;
	}
	return (no_esc_file);
}

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
	char		*no_esc_file;
	char		*tmp;

	no_esc_file = remove_esc(file);
	lstat(no_esc_file, &st);
	tmp = color[0];
	if (S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode))
		tmp = get_sp_color(st);
	else if (S_ISCHR(st.st_mode))
		tmp = color[1];
	else if (S_ISBLK(st.st_mode))
		tmp = color[2];
	else if (S_ISFIFO(st.st_mode))
		tmp = color[3];
	else if (S_ISLNK(st.st_mode))
		tmp = color[4];
	else if (S_ISSOCK(st.st_mode))
		tmp = color[5];
	else if (S_ISREG(st.st_mode))
		tmp = (is_exec(file)) ? get_sp_color(st) : color[0];
	free(no_esc_file);
	return (tmp);
}
