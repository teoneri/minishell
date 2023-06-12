/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:25:35 by mneri             #+#    #+#             */
/*   Updated: 2023/06/12 15:36:41 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_init_node(t_list *lst)
{
	t_store	*stor;

	lst = malloc(sizeof(t_list));
	stor = malloc(sizeof(t_store));
	stor->whole_cmd = NULL;
	stor->whole_path = NULL;
	stor->infile = STDIN_FILENO;
	stor->outfile = STDOUT_FILENO;
	stor->here_doc = NULL;
	lst->content = (void *)stor;
	lst->next = NULL;
	return (lst);
}

char	*ft_path(char *cmd, t_carry *prompt)
{
	int		i;
	char	**paths;
	char	*path;
	char	*tmp;

	i = ft_findenv("PATH", prompt);
	if (i == -1)
		return (ft_strdup(cmd));
	paths = ft_split(prompt->envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			ft_freepath(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_freepath(paths);
	return (ft_strdup(cmd));
}

char	**ft_strtrim_all(char **splt)
{
	int	i;

	i = 0;
	while (splt[i] != NULL)
	{
		if (splt[i][0] == '\'')
			splt[i] = ft_strtrim(splt[i], "\'");
		else if (splt[i][0] == '\"')
			splt[i] = ft_strtrim(splt[i], "\"");
		i++;
	}
	return (splt);
}

t_store	*fill_node_support(t_list *lst, t_store *stor)
{
	lst->next = ft_init_node(lst->next);
	stor = (t_store *)lst->next->content;
	lst = lst->next;
	return (stor);
}

t_list	*ft_fillnode(char **splt, t_list *lst, t_carry *prompt)
{
	t_list	*head;
	t_store	*stor;
	int		i;

	i = 0;
	splt = ft_strtrim_all(splt);
	lst = NULL;
	lst = ft_init_node(lst);
	stor = (t_store *)lst->content;
	head = lst;
	while (splt[i])
	{
		if (ft_strchr(splt[i], '>') || ft_strcmp(splt[i], ">>") == 0)
			get_outfile(splt, &i, stor);
		else if (ft_strchr(splt[i], '<') || ft_strcmp(splt[i], "<<") == 0)
			get_infile(splt, &i, stor);
		if (ft_strchr(splt[i], '|'))
			stor = fill_node_support(lst, stor);
		else
			ft_get_cmd_path(stor, splt, prompt, &i);
		i++;
	}
	return (head);
}
