/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:44:11 by mneri             #+#    #+#             */
/*   Updated: 2023/05/03 14:44:12 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wordcount(const char *str, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			count++;
			return (count);
		}
		if (*str != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (*str == c)
		{
			flag = 0;
		}
		str++;
	}
	return (count);
}

char	*ft_word_create(char *s, int start, char c)
{
	int		i;
	char	*word;
	int		k;

	k = 0;
	i = start;
	while (s[start] != c && s[start] != '\0')
	{
		start++;
		k++;
	}
	k++;
	word = malloc(sizeof(char) * k + 1);
	k = 0;
	while (s[i] != c && s[i] != '\0')
	{
		word[k] = s[i];
		i++;
		k++;
	}
	word[k] = '\0';
	return (word);
}

char	**ft_splitter(char *s, char **splt, char c, int i)
{
	int	flag;
	int	k;

	k = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '\'' || s[i] == '\"') && flag == 0)
		{
			splt[k] = ft_word_create(s, i + 1, s[i]);
			splt[k + 1] = NULL;
			return (splt);
		}
		else if (s[i] != c && flag == 0)
		{
			splt[k] = ft_word_create(s, i, c);
			k++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
		i++;
	}
	splt[k] = NULL;
	return (splt);
}

char	**ft_pipe_split(char *s, char c)
{
	char	**splt;
	int		i;

	splt = malloc(sizeof(char *) * (wordcount(s, c) + 1));
	i = 0;
	splt = ft_splitter(s, splt, c, i);
	return (splt);
}
