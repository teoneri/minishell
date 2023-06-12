/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:44:34 by lfai              #+#    #+#             */
/*   Updated: 2023/06/12 15:48:16 by lfai             ###   ########.fr       */
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

char	**get_cmd(char **splt, int *i)
{
	char	**str;
	int		k;
	int		start;
	int		j;

	j = 0;
	start = *i;
	k = 0;
	while (!ft_strchr(splt[*i], '|') && !ft_strchr(splt[*i], '>') \
	&& splt[*i])
	{
		k++;
		*i += 1;
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
	return (str);
}

void	ft_get_cmd_path(t_store *stor, char **splt, t_carry *prompt, int *i)
{
	stor->whole_path = ft_path(splt[*i], prompt);
	stor->whole_cmd = get_cmd(splt, i);
}
