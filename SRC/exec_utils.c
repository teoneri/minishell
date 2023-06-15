/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:23:28 by mneri             #+#    #+#             */
/*   Updated: 2023/06/15 16:25:56 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_continuebuiltin(t_store *stor, t_carry *prompt, char ***str, int len)
{
	if (ft_strncmp(stor->whole_cmd[0], "exit", len) == 0 && len == 4)
	{
		ft_exit(prompt, *str);
	}
	return (0);
}

void	ft_continue_exec(t_store *stor, t_carry *prompt, char ***str)
{
	if (stor->outfile != 1)
	{
		if (dup2(stor->outfile, STDOUT_FILENO) < 0)
			ft_error(DUPERROR, 1);
	}
	if (ft_checkbuiltin(stor, prompt, str))
		;
	else
		g_status = ft_exec_cmd(stor, prompt, *str);
}

void	ft_finish_exec(t_carry *prompt, t_list *head, int *stin, int *stout)
{
	prompt->cmd = head;
	ft_lstclear(&prompt->cmd, ft_freecontent);
	dup2(*stin, STDIN_FILENO);
	dup2(*stout, STDOUT_FILENO);
}

int	ft_checkpipe(t_list *cmd)
{
	if (cmd->next == NULL)
		return (0);
	else
		return (1);
}

/*!
 * @brief this ft handles the infile and the outfile in the executor
 * @param infile
 * @param type
 * @return
 */
int	hande_file(int infile, int type)
{
	if (infile == -1)
		return (-1);
	if (infile != 0 && type == 1)
	{
		if (dup2(infile, STDIN_FILENO) < 0)
			ft_error(DUPERROR, 1);
	}
	return (0);
}
