/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:37:29 by mneri             #+#    #+#             */
/*   Updated: 2023/05/11 15:44:29 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_wordcount(const char *str, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '\"' )&& flag == 0)
		{
			count++;
			flag = 1;
			if(*str == '\"')
			{
				str++;
				while(*str != '\"' && *str != '\0')
					str++;
			}
			else if(*str == '\'')
			{
				str++;
				while(*str != '\'' && *str != '\0')
					str++;
			}
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

char	*ft_cmdword_create(char *s, int start, char c)
{
	int		i;
	char	*word;
	int		k;
	int		j;

	j = 0;
	k = 1;
	i = start;
	start++;
	while (s[start] != c && s[start] != '\0')
	{
		start++;
		k++;
	}
	k++;
	word = malloc(sizeof(char) * k + 1);
	while (s[i] != '\0' && j < k + 1)
	{
		word[j] = s[i];
		i++;
		j++;
	}
	word[k] = '\0';
	return (word);
}

char	**ft_cmdsplitter(char *s, char **splt, char c, int i)
{
	int	flag;
	int	k;
	int temp;

	k = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '\'' || s[i] == '\"') && flag == 0)
		{
			splt[k] = ft_cmdword_create(s, i, s[i]);
			temp = s[i];
			i++;
			while(s[i] != temp)
				i++;
			k++;
			flag = 1;
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

char	**ft_cmdtrim(char *s, char c)
{
	char	**splt;
	int		i;

	splt = malloc(sizeof(char *) * (cmd_wordcount(s, c) + 1));
	i = 0;
	splt = ft_cmdsplitter(s, splt, c, i);
	return (splt);
}
;;