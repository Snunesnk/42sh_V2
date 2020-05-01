/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:41:59 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/01 13:53:31 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	free_rec(t_job *j)
{
	if (j)
	{
		free_rec(j->next);
		free_a_job(j);
	}
}

void		free_all_jobs(void)
{
	if (g_first_job)
	{
		free_rec(g_first_job);
		g_first_job = NULL;
	}
}
