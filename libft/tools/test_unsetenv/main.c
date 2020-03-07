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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "errno.h"

int main(void)
{
	extern char	**environ;
	int		ret;
	ret = 0;

	printf("\n");
	
	errno = 0;
	printf("TE\n");
	ft_print_tables(environ);
	ret = unsetenv("TE");
	printf("%d\n", ret);
	perror(NULL);
	
	errno = 0;
	setenv("TEST1", "test1", 1);
	setenv("TEST2", "test2", 1);
	setenv("TEST3", "test3", 1);
	setenv("TEST4", "test4", 1);
	setenv("TEST5", "test5", 1);
	setenv("TEST6", "test6", 1);
	setenv("TEST7", "test7", 1);
	setenv("TEST8", "test8", 1);
	setenv("TEST9", "test9", 1);
	
	errno = 0;
	printf("TEST\n");
	ft_print_tables(environ);
	ret = unsetenv("TEST");
	printf("%d\n", ret);
	perror(NULL);
	printf("\n");
	
	errno = 0;
	printf("TEST1\n");
	ft_print_tables(environ);
	ret = unsetenv("TEST1");
	ft_printf("%d\n", ret);
	perror(NULL);
	printf("\n");
	
	errno = 0;
	printf("TEST1=\n");
	ft_print_tables(environ);
	ret = unsetenv("TEST1=");
	printf("%d\n", ret);
	perror(NULL);
	printf("\n");

	errno = 0;
	printf("TEST2\n");
	ft_print_tables(environ);
	ret = unsetenv("TEST2");
	ft_printf("%d\n", ret);
	perror(NULL);
	printf("\n");

	errno = 0;
	printf("(null)\n");
	ft_print_tables(environ);
	ret = unsetenv(NULL);
	ft_printf("%d\n", ret);
	perror(NULL);
	printf("\n");

	errno = 0;
	printf("\"\"\n");
	ft_print_tables(environ);
	ret = unsetenv("");
	ft_printf("%d\n", ret);
	perror(NULL);
	printf("\n");

	errno = 0;
	printf("\"TEST3:\"\n");
	ft_print_tables(environ);
	ret = unsetenv("TEST3:");
	ft_printf("%d\n", ret);
	perror(NULL);
	printf("\n");

	return (0);
}
