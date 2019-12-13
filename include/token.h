/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:11:03 by efischer          #+#    #+#             */
/*   Updated: 2019/12/04 16:43:34 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"

# define NB_TOKEN	13
# define TAB_END	-1 

enum	e_token
{
	PIPE,
	AND,
	SEMICOLON,
	OP_BRACKET,
	CL_BRACKET,
	R_DB_REDIR,
	L_DB_REDIR,
	R_REDIR,
	L_REDIR,
	WORD,
	COMMENT,
	START,
	END
};

typedef struct		s_token
{
	int		type;
	char			*value;
}					t_token;


int		lexer(const char* str, t_list **lst);
int		parser(t_list *lst);
void	debug(t_list *lst);

#endif
