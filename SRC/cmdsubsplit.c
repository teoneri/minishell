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

char	*ft_splitspecchar(char *s, char spechars)
{
	char *splt;

	if(s[0] == spechars || s[ft_strlen(s) - 1] == spechars)
	{
		splt = ft_strdup(&spechars);
		return splt;
	}
	else
	{
		splt = ft_substr(s, 0, ft_strlen(s) - 1);
		return (splt);
	}
}

char	**ft_splisplt(char **s, char **splt, int wordnum)
{
	int i;
	int j;
	int k;
	char spechars[3] = {'|', '>', '<'};

	j = 0;
	i = 0;
	k = 0;
	while(i < wordnum)
	{
		if((ft_strchr(s[j], spechars[0])
		|| ft_strchr(s[j], spechars[1])
		|| ft_strchr(s[j], spechars[2])) 
			&& !ft_strchr2(s[j], '\'', '\"'))
		{
			splt[i] = ft_splitspecchar(s[j], spechars[k]);
			i++;
		}
		else
			splt[i] = ft_strdup(s[j]);
		i++;
		j++;
	}
	return(splt);
}

char	**ft_cmdsubsplit(char **s)
{
	char	**splt;
	int		wordnum;

	wordnum = wordcount(s);
	splt = malloc(sizeof(char *) * (wordnum + 1));
	splt = ft_splisplt(s, splt, wordnum);
	return (splt);
}
