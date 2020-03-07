#include "libft.h"

static t_list	*get_tail(t_list *elem)
{
	while (elem && elem->next)
		elem = elem->next;
	return (elem);
}

static t_list *partition(t_list *head, t_list *end, t_list **newhead, t_list **newtail, int (*cmp)(void *, void *))
{
	t_list *pivot;
	t_list *prev;
	t_list *cur;
	t_list *tail;
	t_list *tmp;

	pivot = end;
	prev = NULL;
	cur = head;
	tail = pivot;
	while (cur != pivot)
	{
		if (cmp(cur->content, pivot->content) < 0)
		{
			if (*newhead == NULL)
				*newhead = cur;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			if (prev)
				prev->next = cur->next;
			tmp = cur->next;
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}
	if (*newhead == NULL)
		*newhead = pivot;
	*newtail = tail;
	return (pivot);
}

static t_list	*quicksort_recursion(t_list *head, t_list *tail, int (*cmp)(void *, void *))
{
	t_list	*newhead;
	t_list	*newtail;
	t_list	*pivot;
	t_list	*tmp;

	newhead = NULL;
	newtail = NULL;
	pivot = NULL;
	if (!head || head == tail)
		return head;
	pivot = partition(head, tail, &newhead, &newtail, cmp);
	if (newhead != pivot)
	{
		tmp = newhead;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		newhead = quicksort_recursion(newhead, tmp, cmp);
		tmp = get_tail(newhead);
		tmp->next = pivot;
	}
	pivot->next = quicksort_recursion(pivot->next, newtail, cmp);
	return (newhead);
}

void		ft_lstquicksort(t_list **alst, int (*cmp)(void *, void *))
{
	*alst = quicksort_recursion(*alst, get_tail(*alst), cmp);
}
