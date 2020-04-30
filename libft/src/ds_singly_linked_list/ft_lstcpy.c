/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:06:58 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/09 14:46:35 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *lst, t_list *(*f)(t_list*))
{
	t_list	*new;

	if (f == NULL)
		return (NULL);
	new = f(lst);
	return (new);
}
