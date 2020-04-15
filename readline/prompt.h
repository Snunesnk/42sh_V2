/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 22:17:47 by snunes            #+#    #+#             */
/*   Updated: 2020/04/15 12:54:06 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define GREEN_ARROW "\033[38;5;47m\u279c \033[0m"
# define RED_ARROW "\033[38;5;196m\u279c \033[0m"
# define PROMPT_COLOR "\033[38;5;117m"
# define END_SIGN "\033[0m\033[38;5;231m \u00BB \033[0m"

char	*get_prompt(void);
size_t	get_vis_prompt_len(char *prompt);

#endif
