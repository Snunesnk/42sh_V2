/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:47:48 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 17:01:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int main(void)
{
	char *s;

	s = ft_strdup("/home//.////antoine");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("./home/./antoine");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/./home/./antoine/./");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/./home/./antoine/.");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("//");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("///");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/.//");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/././.");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);

	ft_printf("\n\n-------------   /../   -------------- \n");
	s = ft_strdup("/home/antoine/../Minishell");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/home/../antoine");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/home/antoine/../");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("../home/antoine");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/../home/antoine/./");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/../home/../antoine/.");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("../");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/../");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("//../");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/...//");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);
	s = ft_strdup("/../../..");
	ft_printf("%s\n", ft_resolvepath(s));
	free(s);

	return (0);
}
