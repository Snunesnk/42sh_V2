#include <stdlib.h>

#include "libft.h"
#include "ft_errno.h"
#include "ft_queue.h"
#include "error.h"
#include "tokens.h"

/* ------------------------------- UTILS -----------------------------------------------*/

static int	get_token_type(char *str) /* get the token type comparing first characters of str with known token in grammar */
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

static char	*get_token_symbol(int token) /* return pointer to the grammar symbol corresponding to the token type */
{
	int	i;

	i = 0;
	while (g_grammar_symbols[i].type != -1)
	{
		if (g_grammar_symbols[i].type == token)
			return (g_grammar_symbols[i].symbol);
		++i;
	}
	return (NULL);
}

/* --------------------------------- GET NEXT TOKEN ------------------------------------ */

char	*get_word(char **input)
{
	char	*word;
	int	i;
	char	quote_type;
	_Bool	open_quotes;

	i = 0;
	open_quotes = 0;
	while ((*input)[i])
	{
		if (!open_quotes && ((*input)[i] == '\'' || (*input)[i] == '\"')) /* check if quotes are open */
		{
			open_quotes ^= 1;
			quote_type = (*input)[i];
			++i;
			continue;
		}
		if (!open_quotes && (get_token_type(&(*input)[i]) != -1 || ((*input)[i] == ' ' || (*input)[i] == '\t'))) /* stop if meet other token or delimiter */
			break;
		if ((*input)[i] == quote_type) /* Handle closing quotes */
		{
			++i;
			open_quotes ^= 1;
			continue;
		}
		if ((*input)[i] == '\\' &&
			((open_quotes && quote_type != '\'') || !open_quotes)) /* handle backslashes and single quote cases  */
			++i;
		++i;
	}
	if (!(word = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	word = (char*)ft_memcpy((void*)word, (void*)(*input), i); /* Copy the part of the string that has been
									above-identified as WORD token */
	*input += i;
	return (word);
}

/* Function copy the io_number to the symbol section of a token */
static t_token	get_io_number(char *io_nb_start, char *io_nb_end)
{
	t_token token;

	token.type = IO_NUMBER;
	token.symbol = ft_strndup(io_nb_start, (size_t)(io_nb_end - io_nb_start)); /* Copy the "numbers" into a string */
	if (!token.symbol)
	{
		g_errno = E_ENOMEM; /* If malloc failed, g_errno is set for further error mgt  */
		return ((t_token){0}); /* return empty token */
	}
	return (token);
}

/* Analyze the input string and eat the first chunck of that input which correspond to a token */
t_token	tokenizer(char **input)
{
	t_token	token;
	char	*str;
	char	*digit_start;

	str = *input;
	token = (t_token){.symbol = NULL, .type = -1}; /* set to "no type" the token */
	while (*str == ' ' || *str == '\t') /* skip all useless characters */
		++str;
	if (!*str) /* Jump to the end if no more input. */
		return (token);
	if (ft_isdigit(*str)) /* check for IO_NUMBER */
	{
		digit_start = str;
		while (ft_isdigit(*str)) /* skip digit to know if a <, <<, > or >> follows the digit,
					in this case the number is a IO_NUMBER, eg ls 124> toto */
			++str;
		if (*str == '>' || *str == '<')
		{
			token = get_io_number(digit_start, str); /* get the io_number abd return it
									as token, e.g. ls 2> ok, 2 is io_number */
			*input = str; /* set input line read to the end of the taken token */
		}
	}
	else if ((token.type = get_token_type(str)) != -1) /* get token type if among metacharacters */
	{
		token.symbol = ft_strdup(get_token_symbol(token.type)); /* get symbol of the token of known type */
		*input += ft_strlen(token.symbol); /* Move input to next token */
	}
	else /* treat input as it is a word token */
	{
		*input = str;
		token.type = WORD;
		token.symbol = get_word(input); /* get symbol and move input to next token */
	}
	return (token);
}

/* malloc a token and set its value before returning it to the lexer */
t_token	*get_next_token(char **input)
{
	t_token	*token;

	token = (t_token*)ft_memalloc(sizeof(t_token));
	if (!token) /* if malloc fails, g_errno value is set */
	{
		g_errno = E_ENOMEM;
		return (NULL);
	}
	*token = tokenizer(input); /* assign value of the token without memcpy */
	if (token->type == -1) /* if type does not exist, then the token is empty. */
		return (NULL);
	return (token);
}

/* ------------------------------------------------- LEXER -------------------------------------- */

/* this function will transform the input into token.
   token will be put into a queue */
int	lexer(char *input, struct s_queue *queue)
{
	t_token	*token;

	while ((token = get_next_token(&input))) /* Get a token from the input until no more token */
	{
		queue_enqueue(queue, token); /* Put that token into a queue to speed up the recursive descent during parsing */
		ft_printf("symbol: %s\n", token->symbol);/* deebug */
		ft_printf("type: %d\n\n", token->type);/* deebug */
	}
	if (g_errno == E_ENOMEM) /* If a malloc failed, g_errno set error value and then return the corresponding error value */
		return (e_cannot_allocate_memory);
	return (e_success);
}
