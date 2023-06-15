/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:44:34 by lfai              #+#    #+#             */
/*   Updated: 2023/06/15 16:44:32 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_outfile(char **splt, int *i, t_store *stor)
{
	if (stor->outfile > 2)
		close(stor->outfile);
	if (!ft_strcmp(splt[*i], ">") && splt[*i + 1])
		stor->outfile = open(splt[*i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	else
		stor->outfile = open(splt[*i + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	if (stor->outfile < 0)
		ft_error(FDERROR, 1);
	if (splt[*i + 1])
		*i += 1;
}

void	get_infile(char **splt, int *i, t_store *stor)
{
	if (stor->infile > 2)
		close(stor->infile);
	if (!ft_strcmp(splt[*i], "<"))
		stor->infile = open(splt[*i + 1], O_RDONLY, 0644);
	else
		stor->here_doc = ft_strdup(splt[*i + 1]);
	if (stor->infile < 0)
		ft_error(FDERROR, 1);
	if (splt[*i + 2])
		*i += 1;
}

void	ft_freepath(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

int	update_cmd_pos(int k, int *i, char **splt)
{
	k++;
	*i += 1;
	if (splt[*i] && !ft_checkquote(splt[*i]))
	{
		k++;
		*i += 1;
	}
	return (k);
}

char	**get_cmd(char **splt, int *i)
{
	char	**str;
	int		k;
	int		start;
	int		j;

	j = 0;
	start = *i;
	k = 0;
	while ((!ft_strchr(splt[*i], '|') && !ft_strchr(splt[*i], '>')) \
	&& splt[*i])
	{
		k = update_cmd_pos(k, i, splt);
	}
	*i -= 1;
	str = malloc(sizeof(char *) * (k + 1));
	while (k-- > 0)
	{
		str[j] = ft_strdup(splt[start]);
		j++;
		start++;
	}
	str[j] = NULL;
	str = ft_strtrim_all(str);
	return (str);
}
