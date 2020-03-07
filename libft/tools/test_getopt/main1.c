#include "libft.h"
#include "ft_getopt.h"
#include "ft_errno.h"
#include "ft_wchar.h"

#include <wchar.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <strings.h>

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

/* Test GETOPT */
	char	ft_getoptret = 0;
	char	getoptret = 0;
	int	getopt_argc = 5;
	char	optstring[] = "-Rarln:c:";/* 
	char	optstring[] = "-Rarln:c:"; */
	char	*getopt_argv[7];
	char	*str0_opt;
	char	str1_opt[] = "-R:aorlt";
	char	str2_opt[] = "--";
	char	str3_opt[] = "-ac=l50";
	char	str4_opt[] = "--";
	char	str5_opt[] = "merde";
	int	i = 1;
	
	str0_opt = argv[0];
	getopt_argv[0] = str0_opt;
	getopt_argv[1] = str1_opt;
	getopt_argv[2] = str2_opt;
	getopt_argv[3] = str3_opt;
	getopt_argv[4] = str4_opt;
	getopt_argv[5] = str5_opt;
	getopt_argv[5] = NULL;
	
	printf("optstring => %s\n", optstring);
	//ft_sortopt(getopt_argc, getopt_argv, ":");
	ft_print_tables(getopt_argv);
	g_opterr = 0;
	opterr = 0;
	while (i < 28)
	{
		ft_getoptret = ft_getopt(getopt_argc, getopt_argv, optstring);
	//	getoptret = getopt(getopt_argc, getopt_argv, optstring);
	//	printf("\n      ret, optopt:optarg, optind, opterr\n");
	//	printf("libc:%d%3c,%6c:%10s,%5d,%5d\n", (int)getoptret, getoptret, optopt, optarg, optind, opterr);
		printf("lbft:%d%3c,%6c:%10s,%5d,%5d\n", (int)ft_getoptret, ft_getoptret, g_optopt, g_optarg, g_optind, g_opterr);
		++i;
	}
	ft_print_tables(getopt_argv);
	printf("\n===================== RESET ===========================\n");
	i = 1;
#ifdef __unix__
	g_optind = 0;
	optind = 0;
#else
	g_optind = 0;
	optind = 0;
	optreset = 1;
#endif
//	ft_print_tables(getopt_argv);
	while (i < 28)
	{
		ft_getoptret = ft_getopt(getopt_argc, getopt_argv, optstring);
	//	getoptret = getopt(getopt_argc, getopt_argv, optstring);
	//	printf("\n      ret, optopt:optarg, optind, opterr\n");
	//	printf("libc:%d%3c,%6c:%10s,%5d,%5d\n", (int)getoptret, getoptret, optopt, optarg, optind, opterr);
		printf("lbft:%d%3c,%6c:%10s,%5d,%5d\n", (int)ft_getoptret, ft_getoptret, g_optopt, g_optarg, g_optind, g_opterr);
		++i;
	}
//	printf("%d\n", g_optind);
//	printf("%d\n", g_optind);
	
	return (0);
}
