/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsubsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:04:35 by mneri             #+#    #+#             */
/*   Updated: 2023/05/17 16:24:48 by mneri            ###   ########.fr       */
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

int	ft_checkquote(char *s)
{
	int  i;

	i = 0;
	while(s[i])
	{
		if(s[i] == '>' || s[i] == '<' || s[i] == '|')
			return (1);
		if(s[i] == '\'' || s[i] == '\"' )
		{
			i++;
			while(s[i] != '\'' && s[i] != '\"' && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (0);
}

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
			if(ft_checkquote(str[i]))
			{
				count += ft_speccount(str[i], spechars[k]);
				k = 0;
				break;
			}
			k++;
		}
		k = 0;
		i++;
	}
	return count;
}

int ft_skipquote(char *s, int i)
{
	if(s[i] == '\'' || s[i] == '\"')
	{
		i++;
		while(s[i] != '\'' && s[i] != '\"')
			i++;
	}
	return i;
}

int ft_splisplt(char **s, char **splt, int y, int i)
{
	
	int k = 0;
	int j = 0;

	while (s[i][j])
	{
		int z = 0;
		k = j;
		if(s[i][j] == '\'' || s[i][j] == '\"')
			j = ft_skipquote(s[i], j);
		while (s[i][j] != '|' && s[i][j] != '>' 
		&& s[i][j] != '<' && s[i][j] != '\0')
			j++;
		if (j != 0 && s[i][k] != '|' && s[i][k] != '>' && s[i][k] != '<')
		{
			splt[y] = malloc(sizeof(char) * (j + 1));
			while (z < j)
			{
				splt[y][z] = s[i][k];
				z++;
				k++;
			}
			splt[y][z] = '\0';
		}
		else
		{
			splt[y] = malloc(sizeof(char) * 2);
			splt[y][0] = s[i][j];
			splt[y][1] = '\0';
			j++;		
		}
		y++;
	}
	return y;
}

char **ft_cmdsubsplit(char **s)
{
	char **splt;
	int wordnum;

	static int y = 0;
	int i = 0;

	wordnum = wordcount(s);
	splt = malloc(sizeof(char *) * (wordnum + 1));
	while(s[i])
	{
		if((ft_strchr(s[i], '|') || ft_strchr(s[i], '>') 
		|| ft_strchr(s[i], '<'))&& ft_checkquote(s[i]))
		{
			y = ft_splisplt(s, splt, y, i);
		}
		else
		{
			splt[y] = s[i];
			y++;
		}
		i++;
	}
	splt[wordnum + 1] = NULL;
	return (splt);
}