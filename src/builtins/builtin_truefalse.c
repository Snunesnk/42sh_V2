/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_truefalse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/18 09:50:32 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	cmd_true(int argc, t_process *p)
{
	(void)argc;
	(void)p;
	return (1);
}

int	cmd_false(int argc, t_process *p)
{
	(void)argc;
	(void)p;
	return (0);
}
