/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:25:35 by mneri             #+#    #+#             */
/*   Updated: 2023/05/23 17:50:15 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_carry	*ft_initNode(t_carry *lst)
{
	t_store	*stor;

	lst = (t_carry *)malloc(sizeof(t_carry));
    lst->cmd = (t_list *)malloc(sizeof(t_list));
	stor = (t_store *)malloc(sizeof(t_store));
	
	stor->whole_cmd = NULL;  
    stor->whole_path = NULL; 
    stor->infile = STDIN_FILENO;        
    stor->outfile = STDOUT_FILENO;

	lst->cmd->content = (void *)stor;
	lst->cmd->next = NULL;
	return(lst);
	
}

void	get_outfile(char **splt, int *i, t_store *stor)
{
	if(stor->outfile > 2)
		close(stor->outfile);
	if(splt[*i + 1])
		stor->outfile = open(splt[*i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	*i += 1;
}

void	get_infile(char **splt, int *i, t_store *stor)
{	if(stor->infile > 2)
		close(stor->infile);
	stor->infile = open(splt[*i + 1], O_RDONLY, 0644);
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

void	ft_freestor(t_store *stor)
{
	free(stor->whole_cmd);
	free(stor->whole_path);
	free(stor);
}

t_list	*storeinit(t_list *cmd)
{
	t_store *store;

	cmd = (t_list *)malloc(sizeof(t_list));
	store = (t_store *)malloc(sizeof(t_store));
	store->whole_cmd = NULL;  
    store->whole_path = NULL; 
    store->infile = STDIN_FILENO;        
    store->outfile = STDOUT_FILENO;
	
	cmd->content = (void*)store;
	cmd->next = NULL;
	ft_freestor(store);
	return cmd;
}

// (t_list *)ft_initNode((t_carry *)lst->cmd->next)

t_carry *ft_fillnode(char **splt)
{
    t_carry *lst;
	t_carry *head;
    t_store *stor;
    static int i = 0;

    lst = NULL;
	
    lst = ft_initNode(lst);
    stor = (t_store *)lst->cmd->content;
	head = lst;
    while (splt[i])
    {
        if (ft_strchr(splt[i], '>'))
            get_outfile(splt, &i, stor);
        else if (ft_strchr(splt[i], '<'))
            get_infile(splt, &i, stor);
        else if (ft_strchr(splt[i], '|'))
        {
			lst->cmd->next = storeinit(lst->cmd->next);
			stor = (t_store *)lst->cmd->next->content;
			lst = (t_carry *)lst->cmd->next;
			
        }
        else
            get_cmd(splt, &i, stor);
        i++;
    }
    return head;
}