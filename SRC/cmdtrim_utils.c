/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:26:56 by mneri             #+#    #+#             */
/*   Updated: 2023/06/12 14:06:26 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_quoteword(int count, char *str)
{
	count++;
	if (*str == '\"')
	{
		str++;
		while (*str != '\"' && *str != '\0')
			str++;
	}
	else if (*str == '\'')
	{
		str++;
		while (*str != '\'' && *str != '\0')
			str++;
	}
	return (count);
}

int	ft_getwordsize(char *s, int *start, int c, int k)
{
	while (s[*start] != c && s[*start] != '\0')
	{
		*start += 1;
		k++;
	}
	while (s[*start] != ' ' && s[*start] != '\0')
	{
		*start += 1;
		k++;
	}
	return (k);
}

void	ft_nextquote(char *s, int *i, int *k, int *flag)
{
	int temp;
	
	temp = s[*i];
	i++;
	while (s[*i] != temp && s[*i] != '\0')
		*i += 1;
	*k += 1;
	*flag = 1;
}