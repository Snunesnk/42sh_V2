#include "libft.h"
#include "shell.h"
#include "quotes.h"

int		g_oneline = 0;

static int	reset_return(int err)
{
	g_eof = 0;
	g_input_break = 0;
	g_subprompt = 0;
	return (err);
}

static int	subprompt_full_quote(int fd, t_list **lst, int qmode)
{
	char	*input;
	char	*tmp;

	input = get_input_fd(fd, qmode, "> ");
	if (g_eof || !input)
	{
		psherror(e_unexpected_eof_2, NULL, e_invalid_type);
		free(input);
		exit_clean(g_errordesc[e_unexpected_eof_2].code);
	}
	if (g_input_break)
	{
		ft_memdel((void**)&input);
		return (reset_return(e_unexpected_eof_130));
	}
	tmp = ft_strjoin(input, "\n");
	free(input);
	input = tmp;
	*lst = lexer(input);
	free(input);
	return (reset_return(e_success));
}

int			subprompt(int fd, t_list **lst, int qmode)
{
	char	*input;

	g_subprompt = 1;
	if (qmode == BSQUOTE)
	{
		input = heredoc(fd, &((t_token*)((*lst)->next->content))->value, qmode);
		free(((t_token*)((*lst)->next->content))->value);
		((t_token*)((*lst)->next->content))->value = input;
		if (g_eof)
			return (reset_return(e_heredoc_warning));
		else if (g_input_break)
			return (reset_return(e_unexpected_eof_130));
		return (reset_return(e_success));
	}
	else if (qmode == FULL_QUOTE)
		return (subprompt_full_quote(fd, lst, qmode));
	return (reset_return(e_success));
}
