#include "libft.h"
#include "error.h"
#include "shell.h"

/* ************************************************* **
**                                                   **
**             PARSE/BUILD REDIRECTIONS              **
**                                                   **
** ************************************************* */

static t_redirection	*parse_redirection(t_list **lst)
{
	int		io_nb;

	/* Parse IO_NB if ther is one */
	if (get_tokentype(*lst) == IO_NB)
	{
		io_nb = ft_atoifd(get_tokvalue(*lst));
		(*lst) = (*lst)->next;
	}
	else
		io_nb = -1;
	return (set_redirection(lst, io_nb));
}

void	debug_r(t_redirection *r)
{
	int	i;

	i = 0;
	ft_printf("\n");
	while (r)
	{
		ft_printf("redir:%d\n", i++);
		if (r->redirector.filename)
			ft_printf(">%s\n", r->redirector.filename);
		r = r->next;
	}
	ft_printf("\n");
}

t_redirection	*build_redirections(t_list **lst)
{
	t_redirection	*r;
	t_redirection	**n;

	while (get_tokentype(*lst) != PIPE && get_tokentype(*lst) != END
		&& get_tokentype(*lst) != IO_NB && !is_redir_type(get_tokentype(*lst)))
		(*lst) = (*lst)->next;
//	ft_printf("\n");
//	debug(*lst);
//	ft_printf("\n");
	r = parse_redirection(lst);
	if (r)
		n = &(r->next);
//	debug_r(r);
//	ft_printf("\n");
//	debug(*lst);
//	ft_printf("loop follow\n");
	while (get_tokentype(*lst) != PIPE && get_tokentype(*lst) != END)
	{
//		ft_printf("\n");
//		debug(*lst);
//		ft_printf("\n");
		while (get_tokentype(*lst) != PIPE && get_tokentype(*lst) != END
			&& get_tokentype(*lst) != IO_NB && !is_redir_type(get_tokentype(*lst)))
			(*lst) = (*lst)->next;
 		if (get_tokentype(*lst) == IO_NB || is_redir_type(get_tokentype(*lst)))
		{
			while (has_redirections(get_tokentype(*lst)))
			{
				*n = parse_redirection(lst);
				if (*n)
					n = &((*n)->next);
			}
		}
	}
	debug_r(r); /* Debugging */
	return (r);
}
