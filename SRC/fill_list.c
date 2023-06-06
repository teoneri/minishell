/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:25:35 by mneri             #+#    #+#             */
/*   Updated: 2023/06/06 19:39:56 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_initNode(t_list *lst)
{
	t_store	*stor;

    lst = malloc(sizeof(t_list));
	stor = (t_store *)malloc(sizeof(t_store));
	
	stor->whole_cmd = NULL;  
    stor->whole_path = NULL; 
    stor->infile = STDIN_FILENO;        
    stor->outfile = STDOUT_FILENO;
	stor->here_doc = NULL;
	lst->content = (void *)stor;
	lst->next = NULL;
	return(lst);
	
}

void	get_outfile(char **splt, int *i, t_store *stor)
{
	if(stor->outfile > 2)
		close(stor->outfile);
	if (ft_strchr(splt[*i], '>') && splt[*i + 1])
		stor->outfile = open(splt[*i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	else 
		stor->outfile = open(splt[*i + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	if(stor->outfile < 0)
		ft_error(FDERROR, 1);
	if(splt[*i + 1])
		*i += 1;
}

void	get_infile(char **splt, int *i, t_store *stor)
{	if(stor->infile > 2)
		close(stor->infile);
	if (ft_strchr(splt[*i], '<'))
		stor->infile = open(splt[*i + 1], O_RDONLY, 0644);
	else
		stor->here_doc = ft_strdup(splt[*i + 1]);
	if(stor->infile < 0)
		ft_error(FDERROR, 1);
	*i += 1;
}

void	get_cmd(char **splt, int *i, t_store *stor)
{
	int k;
	int start;
	int j;

	j = 0;
	start = *i;
	k = 0;	
	while(!ft_strchr(splt[*i], '|') && !ft_strchr(splt[*i], '>')
	 && splt[*i])
	{
		k++;
		*i += 1;
	}
	*i -= 1;
	stor->whole_cmd = malloc(sizeof(char*) * (k + 1));
	while(k-- > 0)
	{
		stor->whole_cmd[j] = splt[start];
		j++;
		start++;
	}
	stor->whole_cmd[j] = NULL;
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
}

char	*ft_path(char *cmd, t_carry *prompt)
{
	int		i;
	char	**paths;
	char	*path;
	char	*tmp;

	i = ft_findenv("PATH", prompt);
	if(i == -1)
		return cmd;  
	paths = ft_split(prompt->envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_freepath(paths);
	return (cmd);
}

char	**ft_strtrim_all(char **splt)
{
	int i;

	i = 0;

	while(splt[i] != NULL)
	{
		if(splt[i][0] == '\'')
			splt[i] = ft_strtrim(splt[i], "\'");
		else if(splt[i][0] == '\"')
			splt[i] = ft_strtrim(splt[i], "\"");
		i++;
	}
	return(splt);
}

t_list *ft_fillnode(char **splt, t_list *lst, t_carry *prompt)
{
	t_list *head;
    t_store *stor;
    int i = 0;

	splt = ft_strtrim_all(splt);
    lst = NULL;
    lst = ft_initNode(lst);
    stor = (t_store *)lst->content;
	head = lst;
    while (splt[i])
    {
        if (ft_strchr(splt[i], '>') || ft_strcmp(splt[i], ">>") == 0)
            get_outfile(splt, &i, stor);
        else if (ft_strchr(splt[i], '<') || ft_strcmp(splt[i], "<<") == 0)
            get_infile(splt, &i, stor);
        else if (ft_strchr(splt[i], '|'))
        {
			lst->next = ft_initNode(lst->next);
			stor = (t_store *)lst->next->content;
			lst = lst->next;
        }
        else
		{
			stor->whole_path = ft_path(splt[i], prompt);
            get_cmd(splt, &i, stor);
		}	
        i++;
    }
    return head;
}