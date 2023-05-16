/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsubsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:04:35 by mneri             #+#    #+#             */
/*   Updated: 2023/05/16 17:44:41 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_speccount(char *str, char c)
{
	if(str[0] == c && str[ft_strlen(str) - 1] == c)
		return (2);
	else if(str[0] == c || str[ft_strlen(str) - 1] == c)
		return (1);
	else
		return (2);
}

char	*ft_strchr2(char *s, int c, int k)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c || s[i] == (char) k)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

// char	*ft_quote(char *s, int c, int k)
// {
// 	int  i;

// 	while(s[i] != k && s[i] != c)
// 		i++;
// 	i++;
// 	while(s[i] != k && s[i] != c)
// 		i++;
// 	return((char *)&s[i]);
// }

static int	wordcount(char **str)
{
	int i;
	int count;
	int k;
	char spechars[3] = {'|', '>', '<'};
	
	k = 0;
	i = 0;
	while(str[i] != NULL)
		i++;
	count = i;
	i = 0;
	while(str[i] != NULL)
	{
		while(k < 3)
		{
			if(ft_strchr(str[i], spechars[k]) 
			&& !ft_strchr2(str[i], '\"', '\''))
			{
				count += ft_speccount(str[i], spechars[k]);
				k = 0;
				break;
			}
			k++;
		}
		i++;
	}
	return count;
}

int ft_splisplt(char **s, char **splt, int j, int i)
{
	int k;

	k = 0;
	while (s[i][j] != '|' && s[i][j] != '>' && s[i][j] != '<' && s[i][j] != '\0')
		j++;
	if (j == 0)
	{
		splt[i] = malloc(sizeof(char) * 2);
		splt[i][0] = s[i][j];
		splt[i][1] = '\0';
		j++;
	}
	else
	{
		splt[i] = malloc(sizeof(char) * (j + 1)); // Allocate space for the null terminator
		while (k < j)
		{
			splt[i][k] = s[i][k];
			k++;
		}
		splt[i][k] = '\0'; // Add the null terminator at the end
	}
	return j;
}

char **ft_cmdsubsplit(char **s)
{
	char **splt;
	int wordnum;
	int j;
	int k;
	int i = 0;
	j = 0;
	k = 0;
	wordnum = wordcount(s);
	splt = malloc(sizeof(char *) * (wordnum + 1));
	while(s[i])
	{
		if((ft_strchr(s[i], '|') || ft_strchr(s[i], '>') || ft_strchr(s[i], '<'))
		&& !ft_strchr2(s[i], '\'', '\"'))
		{
			j = ft_splisplt(s, splt, j, i);
		}
		else
		{
			splt[i] = s[i];
		}
		i++;
	}
	splt[wordnum + 1] = NULL;
	return (splt);
}
