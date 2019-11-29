#ifndef TOKENS_H
#define TOKENS_H

enum e_tokens
{
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,

/* The following are the operators (see XBD Operator)
   containing more than one character. */

	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,

/* The following are the reserved words. */

	If,
	Then,
	Else,
	Elif,
	Fi,

/* These are reserved words, not operator tokens, and are
   recognized when reserved words are recognized. */

	Lbrace,
	Rbrace
};

struct s_token
{
	int	type;
	char	*symbol;
};

typedef struct s_token	t_token;

extern struct s_token	g_grammar_symbols[];

#endif
