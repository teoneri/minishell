/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsubsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:44 by mneri             #+#    #+#             */
/*   Updated: 2023/06/14 12:41:10 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_addcount(char **str, int i, char *spechars, int count)
{
	int	k;

	k = 0;
	while (k < 3)
	{
		if (ft_checkquote(str[i]) && ft_strchr(str[i], spechars[k]))
		{
			count += ft_speccount(str[i], spechars[k]);
			k = 0;
			break ;
		}
		k++;
	}
	return (count);
}

static int	wordcount(char **str)
{
	int		i;
	int		count;
	char	*spechars;

	spechars = malloc(sizeof(char) * 4);
	spechars = ft_initchar(spechars);
	i = 0;
	while (str[i] != NULL)
		i++;
	count = i;
	i = 0;
	while (str[i] != NULL)
	{
		count = ft_addcount(str, i, spechars, count);
		i++;
	}
	free(spechars);
	return (count);
}

char	*ft_addword(int j, char *s, int z, int k)
{
	char	*splt;
	int		x;

	x = j - k;
	splt = malloc(sizeof(char) * (x + 1));
	while (z < x)
	{
		splt[z] = s[k];
		z++;
		k++;
	}
	splt[z] = '\0';
	return (splt);
}

int	ft_splisplt(char **s, char **splt, int y, int i)
{
	int	k;
	int	j;
	int	z;

	k = 0;
	j = 0;
	while (s[i][j])
	{
		z = 0;
		k = j;
		if (s[i][j] == '\'' || s[i][j] == '\"')
			j = ft_skipquote(s[i], j);
		while (s[i][j] != '|' && s[i][j] != '>'
		&& s[i][j] != '<' && s[i][j] != '\0')
			j++;
		if (j != 0 && s[i][k] != '|' && s[i][k] != '>' && s[i][k] != '<')
			splt[y] = ft_addword(j, s[i], z, k);
		else
			splt[y] = ft_doubleredir(s, i, &j);
		y++;
	}
	return (y);
}

/*!
 * @brief this ft splits each command in substrings when it finds special
 * characters, but does not when they are inside quotes.
 * @param s
 * @return
 */
char	**ft_cmdsubsplit(char **s)
{
	char	**splt;
	int		wordnum;
	int		y;
	int		i;

	y = 0;
	i = 0;
	wordnum = wordcount(s);
	splt = malloc(sizeof(char *) * (wordnum + 1));
	while (s[i])
	{
		if ((ft_strchr(s[i], '|') || ft_strchr(s[i], '>')
				|| ft_strchr(s[i], '<')) && ft_checkquote(s[i]))
			y = ft_splisplt(s, splt, y, i);
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
