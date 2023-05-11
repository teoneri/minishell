/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsubsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:04:35 by mneri             #+#    #+#             */
/*   Updated: 2023/05/11 15:19:49 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wordcount(const char **str)
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
			if(ft_strchr(str[i], spechars[k]))
			{
				count++;
				k = 0;
				break;
			}
			k++;
		}
		i++;
	}
	return count;
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

char	**ft_splitter(char *s, char **splt, int i)
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

char	**ft_cmdsubsplit(char **s)
{
	char	**splt;
	int		i;

	splt = malloc(sizeof(char *) * (wordcount(s) + 1));
	i = 0;
	splt = ft_splitter(s, splt, i);
	return (splt);
}
