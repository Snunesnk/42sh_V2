/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:27:01 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/19 09:22:58 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

struct	s_exec
{
	t_process	*p;
	pid_t		pid;
	int			mypipe[2];
	int			infile;
	int			outfile;
	int			only_assignments;
};

typedef struct s_exec	t_exec;

#endif
