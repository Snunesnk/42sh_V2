/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop_get_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:09:11 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/23 16:31:35 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stack.h"

void	*stack_pop_get_data(struct s_stack **top)
{
	struct s_stack	*previous;
	void			*data;

	data = NULL;
	if (*top)
	{
		previous = (*top)->previous;
		data = (*top)->data;
		free(*top);
		*top = previous;
	}
	return (data);
}
