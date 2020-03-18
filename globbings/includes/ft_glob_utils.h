#ifndef FT_GLOB_UTILS_H
# define FT_GLOB_UTILS_H

# include "libft.h"
# include <stdint.h>

t_list	*ft_lst_at(t_list *lst, unsigned int nbr);
void	ft_lst_merge(t_list **lst1, t_list *lst2);
t_list	*ft_lst_pop(t_list **lst, unsigned int pop);
void	ft_lst_quicksort(t_list *lst, int len, int (*cmp)(void *, void *));
int	ft_lst_size(t_list *lst);
void	ft_swap_p(uintptr_t *p1, uintptr_t *p2);

#endif
