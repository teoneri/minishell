/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:25:35 by mneri             #+#    #+#             */
/*   Updated: 2023/06/15 17:03:42 by mneri            ###   ########.fr       */
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

int	ft_initpath(char **cmd, t_carry *prompt)
{
	int	i;

	*cmd = ft_strtrim(*cmd, "\'");
	*cmd = ft_strtrim(*cmd, "\"");
	i = ft_findenv("PATH", prompt);
	return (i);
}

char	*ft_path(char **cmd, t_carry *prompt)
{
	int		i;
	char	**paths;
	char	*path;
	char	*tmp;

	i = ft_initpath(cmd, prompt);
	if (i == -1)
		return (ft_strdup(*cmd));
	paths = ft_split(prompt->envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, *cmd);
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
	return (ft_strdup(*cmd));
}

t_store	*fill_node_support(t_list *lst, t_store *stor)
{
	lst->next = ft_init_node(lst->next);
	stor = (t_store *)lst->next->content;
	lst = lst->next;
	return (stor);
}

/*!
 * @brief this ft creates a node when it finds a pipe and fills the node
 * based on the cmd given
 * @param splt
 * @param lst
 * @param prompt
 * @param i
 * @return
 */
t_list	*ft_fillnode(char **splt, t_list *lst, t_carry *prompt, int i)
{
	t_list	*head;
	t_store	*stor;

	lst = ft_init_node(lst);
	stor = (t_store *)lst->content;
	head = lst;
	while (splt[i])
	{
		if (ft_handlefiles(&i, splt, stor))
			;
		else if (ft_checkquote(splt[i]) && ft_strchr(splt[i], '|'))
		{
			lst->next = ft_init_node(lst->next);
			stor = (t_store *)lst->next->content;
			lst = lst->next;
		}
		else
		{
			stor->whole_path = ft_path(&splt[i], prompt);
			stor->whole_cmd = get_cmd(splt, &i);
		}
		i++;
	}
	return (head);
}
