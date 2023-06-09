/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsubsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:44 by mneri             #+#    #+#             */
/*   Updated: 2023/06/09 17:30:10 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int ft_speccount(char *str, char c)
{
	int len;

	len = ft_strlen(str);
	
	if(len == 1)
		return(0);
	else if(str[0] == c && str[len - 1] == c)
		return (2);
	else if(str[0] == c || str[len - 1] == c)
		return (1);
	else if(str[0] != c && str[len - 1] != c)
		return (0);
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
		if(s[i] != '\0')
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
 			if(ft_checkquote(str[i]) && ft_strchr(str[i], spechars[k]))
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
	int	x;
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
			x = j - k;
			splt[y] = malloc(sizeof(char) * (x + 1));
			while (z < x)
			{
				splt[y][z] = s[i][k];
				z++;
				k++;
			}
			splt[y][z] = '\0';
		}
		else
		{
			if(ft_strncmp(s[i], ">>", 2) == 0 || ft_strncmp(s[i], "<<", 2) == 0)
			{
				splt[y] = malloc(sizeof(char) * 3);
				splt[y][0] = s[i][j];
				splt[y][1] = s[i][j + 1];
				splt[y][2] = '\0';
				j += 2;
			}
			else
			{
				splt[y] = malloc(sizeof(char) * 2);
				splt[y][0] = s[i][j];
				splt[y][1] = '\0';
				j++;	
			}
		}
		y++;
	}
	return y;
}

char **ft_cmdsubsplit(char **s)
{
	char **splt;
	int wordnum;

	int y = 0;
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
			splt[y] = ft_strdup(s[i]);
			y++;
		}
		i++;
	}
	splt[wordnum] = NULL;
	ft_freematrix(s);
	return (splt);
}