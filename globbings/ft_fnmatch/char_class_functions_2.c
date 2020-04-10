/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_class_functions_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:24:15 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 13:24:18 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_fnm_is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int	ft_fnm_is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

int	ft_fnm_is_lower(char c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_fnm_is_upper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

int	ft_fnm_is_cntrl(char c)
{
	return ((c >= 0 && c <= 31) || c == 127);
}
