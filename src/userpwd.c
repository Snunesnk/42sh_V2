/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userpwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 18:32:32 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/19 18:37:00 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_user_home(char *start, char *end)
{
	struct passwd	*pwd;
	char			*user;

	if (start && end)
	{
		user = ft_strndup(start, (size_t)(end - start));
		if (!user)
		{
			pwd = getpwnam(user);
			free(user);
			if (pwd)
				return (pwd->pw_dir);
		}
	}
	return (NULL);
}
