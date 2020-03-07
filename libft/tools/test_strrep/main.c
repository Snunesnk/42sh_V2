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
	char	*dst;
	char	*expansion;
	char	*after;

	expansion = "abarthel";

	dst = ft_strdup("df");
	after = ft_strrep(&dst, expansion, "$LOGNAME");
	printf("%s\n", after);
	ft_memdel((void**)&after);

	dst = ft_strdup("/home/$LOGNAME/sfsfasdfasf/safasdf/$LOGNAME/endf");
	after = ft_strrep(&dst, expansion, "$LOGNAME");
	printf("%s\n", after);
	ft_memdel((void**)&after);

	dst = ft_strdup("$LOGNAME");
	after = ft_strrep(&dst, expansion, "$LOGNAME");
	printf("%s\n", after);
	ft_memdel((void**)&after);
	
	dst = ft_strdup("");
	after = ft_strrep(&dst, expansion, "$LOGNAME");
	printf("%s\n", after);
	ft_memdel((void**)&after);
	
	dst = ft_strdup("$LOG$LOGNAMENAME");
	after = ft_strrep(&dst, expansion, "$LOGNAME");
	printf("%s\n", after);
	ft_memdel((void**)&after);

	return (0);
}
