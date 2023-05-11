/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:43:41 by mneri             #+#    #+#             */
/*   Updated: 2022/10/10 13:43:42 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(const char *str, char c)
{
	int	count;
	int	flag;

	flag = 0;
	count = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (count);
}

static char	*stralloc(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof (char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	int		l;
	size_t	j;
	char	**split;

	split = malloc(sizeof(char *) * (wordcount(s, c) + 1));
	i = 0;
	l = -1;
	j = 0;
	if (!split || !s)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && l < 0)
			l = i;
		else if ((s[i] == c || s[i] == '\0') && l >= 0)
		{
			split[j++] = stralloc(s, l, i);
			l = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
