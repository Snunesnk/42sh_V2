/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:23:31 by snunes            #+#    #+#             */
/*   Updated: 2020/04/17 11:51:35 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_UTILS_H
# define FT_GLOB_UTILS_H

# include "libft.h"

t_list	*ft_lst_at(t_list *lst, unsigned int nbr);
void	ft_lst_merge(t_list **lst1, t_list *lst2);
t_list	*ft_lst_pop(t_list **lst, unsigned int pop);
void	ft_lst_quicksort(t_list *lst, int len, int (*cmp)(void *, void *));
int		ft_lst_size(t_list *lst);

#endif
