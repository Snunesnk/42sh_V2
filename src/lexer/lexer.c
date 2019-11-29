#include "libft.h"
#include "ft_errno.h"
#include "ft_queue.h"
#include "error.h"
#include "tokens.h"

static enum e_tokens	get_token_type(char *str)
{
	int	i;

	i = 0;
	while (g_grammar_symbols[i].type != -1)
	{
		if (!ft_strncmp(g_grammar_symbols[i].symbol, str, ft_strlen(g_grammar_symbols[i].symbol)))
			return (g_grammar_symbols[i].type);
		++i;
	}
	return (-1);
}

char	*get_symbol(char **str)
{
	char	*tmp;
	int	i;
	char	quote_type;
	_Bool	open_quotes;

	i = 0;
	open_quotes = 0;
	while ((*str)[i])
	{
			if (!open_quotes && (c == '\'' || c == '\"'))
			{
				open_quotes ^= 1;
				quote_type = (*str)[i];
				++i;
				continue;
			}
			if (!open_quotes && (get_token_type(&(*str)[i]) != -1 || ft_isspace((*str)[i])))
				break;
			if ((*str)[i] == quote_type)
			{
				++i;
				open_quotes ^= 1;
				continue;
			}
			if ((*str)[i] == '\\' &&
				((open_quotes && quote_type != '\'') || !open_quotes))
				++i;
			++i;
	}
	if (!(tmp = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	tmp = (char*)ft_memcpy((void*)tmp, (void*)(*str), i);
	*str += i;
	return (tmp);
}

/* Analyze the input string and eat the first chunck of that input which correspond to a token */
t_token	tokenizer(char *input)
{
	t_token	token;
	char	*start;
	char	*;

	start = input;
	while (*input == ' ' || *input == '\t') /* skip all useless characters */
		++input;
	while (ft_isdigit(input)) /* skip digit to know if a <, <<, > or >> follows the digit,
					in this case the number is a IO_NUMBER, eg ls 124> toto */
		++input;
	/* check if atoi then >> > < << etc
	if (input[x] == '<' || input[x] == '>')
	*/
	token->symbol = get_symbol(input);
	token->type = WORD;
	return (token);
}

/* malloc a token and set its value before returning it to the lexer */
t_token	*get_next_token(char *input)
{
	t_token	*token;

	token = (t_token*)ft_memalloc(sizeof(t_token));
	if (!token) /* if malloc fails, g_errno value is set */
	{
		g_errno = E_ENOMEM;
		return (NULL);
	}
	*token = tokenizer(input); /* assign value of the token without memcpy */
	return (token);
}


/* this function will transform the input into token.
   token will be put into a queue */
int	lexer(char *input, struct s_queue *queue)
{
	t_token	*token;

	while ((token = get_next_token(input))) /* Get a token from the input until no more token */
	{
		queue_enqueue(queue, token); /* Put that token into a queue to speed up the recursive descent during parsing */
	}
	if (g_errno == E_ENOMEM) /* If a malloc failed, g_errno set error value and then return the corresponding error value */
		return (e_cannot_allocate_memory);
	return (e_success);
}
