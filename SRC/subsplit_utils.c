/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsplit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:14:14 by mneri             #+#    #+#             */
/*   Updated: 2023/06/12 16:48:42 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_initchar(char *spechars)
{
	spechars[0] = '|';
	spechars[1] = '>';
	spechars[2] = '<';
	spechars[3] = '\0';
	return (spechars);
}

int	ft_skipquote(char *s, int i)
{
	if (s[i] == '\'' || s[i] == '\"')
	{
		i++;
		while (s[i] != '\'' && s[i] != '\"')
			i++;
	}
	return (i);
}

char	*ft_doubleredir(char **s, int i, int *j)
{
	char	*splt;
	int		k;

	k = *j;
	if (ft_strncmp(s[i], ">>", 2) == 0 || ft_strncmp(s[i], "<<", 2) == 0)
	{
		splt = malloc(sizeof(char) * 3);
		splt[0] = s[i][k];
		splt[1] = s[i][k + 1];
		splt[2] = '\0';
		*j += 2;
	}
	else
	{
		splt = malloc(sizeof(char) * 2);
		splt[0] = s[i][k];
		splt[1] = '\0';
		*j += 1;
	}
	return (splt);
}

int	ft_speccount(char *str, char c)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1)
		return (0);
	else if (str[0] == c && str[len - 1] == c)
		return (2);
	else if (str[0] == c || str[len - 1] == c)
		return (1);
	else if (str[0] != c && str[len - 1] != c)
		return (0);
	else
		return (2);
}

int	ft_checkquote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
			return (1);
		if (s[i] == '\'' || s[i] == '\"' )
		{
			i++;
			while (s[i] != '\'' && s[i] != '\"' && s[i] != '\0')
				i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (0);
}
