/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:56 by mneri             #+#    #+#             */
/*   Updated: 2023/06/09 19:11:53 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

extern int g_status;

int	ft_checkpipe(t_list *cmd)
{
	if(cmd->next == NULL)
		return (0);
	else
		return (1);
}

int	ft_exec_cmd(t_store *stor, t_carry *prompt, char **str)
{
	pid_t id;
	
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	id = fork();
	if(id == -1)
		ft_error(FORKERROR, 1);
	if (id == 0)
	{
		if (execve(stor->whole_path, stor->whole_cmd, prompt->envp) < 0)
		{
			ft_error(CMDNOTFOUND, 127);
			ft_exit(prompt, str);
		}
	}
	{
		g_status = 0;
		// close(fd[0]);
		// close(stor->infile);
		waitpid(id, NULL, 0);
	}
	return g_status;
	
}

int	ft_checkbuiltin(t_store *stor, t_carry *prompt, char ***str)
{
	int len;
	
	len = ft_strlen(stor->whole_cmd[0]);
	if(ft_strncmp(stor->whole_cmd[0], "cd", len) == 0 && len == 2)
	{
		ft_cd(stor, prompt);
		return 1;
	}
	else if(ft_strncmp(stor->whole_cmd[0], "export", len) == 0 && len == 6)
	{
		ft_export(stor, prompt);
		return 1;
	}	
	else if(ft_strncmp(stor->whole_cmd[0], "unset", len) == 0 && len == 5)
	{
		ft_unset(stor, prompt);
		return 1;
	}
	else if((ft_strncmp(stor->whole_cmd[0], "echo", len) == 0 && len == 4)
	&& (ft_strncmp(stor->whole_cmd[1], "$?", 2) == 0 && ft_strlen(stor->whole_cmd[1]) == 2))
	{
		ft_echo();
		return 1;
	}
	else if(ft_strncmp(stor->whole_cmd[0], "exit", len) == 0 && len == 4)
	{
		ft_exit(prompt, *str);
	}
	return 0;

}

void	pipe_ex_child(t_store *stor, int fd[2], t_carry *prompt)
{
	int	id;

	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			ft_error(DUPERROR, 1);
		else if (execve(stor->whole_path, stor->whole_cmd, prompt->envp) < 0)
			ft_error(CMDNOTFOUND, 127);
	}
	else
	{
		g_status = 0;
		wait(&id);
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			ft_error(DUPERROR, 1);
	}
}

t_store *ft_handlepipe(t_list *cmd, t_carry *prompt, t_store *stor, int fd[2])
{
	while(cmd->next != NULL)
	{
		pipe_ex_child(stor, fd, prompt);
		cmd = cmd->next;
		stor = cmd->content;
	}
	if(stor->outfile != STDOUT_FILENO)
	{
		if(dup2(stor->outfile, STDOUT_FILENO) < 0)
			ft_error(DUPERROR, 1);
	}
	return(stor);
}

int hande_file(int infile, int type)
{
	if(infile == -1)
		return -1;
	if(infile != 0 && type == 1)
	{
		if (dup2(infile, STDIN_FILENO) < 0)
			ft_error(DUPERROR, 1);
	}
	return 0;
}

int	ft_exec(t_list *cmd, t_carry *prompt, char ***str)
{
	int fd[2];
	int ogstdin;
	int ogstdout;
	t_store *stor;
	t_list *head = prompt->cmd;

	stor = cmd->content;
	ogstdout= dup(STDOUT_FILENO);
	ogstdin= dup(STDIN_FILENO);
	if(stor->here_doc != NULL)
		stor->infile = ft_handlehere_doc(stor);
	if(hande_file(stor->infile, 1) != -1 && hande_file(stor->outfile, 0) != -1)
	{		
		if(ft_checkpipe(cmd))
		{
			stor = ft_handlepipe(cmd, prompt, stor, fd);
			ft_exec_cmd(stor, prompt, *str);
		}		
		else
		{
			if(stor->outfile != 1)
			{
				if (dup2(stor->outfile, STDOUT_FILENO) < 0)
					ft_error(DUPERROR, 1);
			}
			if(ft_checkbuiltin(stor, prompt, str))
				;
			else
				g_status = ft_exec_cmd(stor, prompt, *str);
		}
	}
	prompt->cmd = head;
	ft_lstclear(&prompt->cmd, ft_freecontent);
	dup2(ogstdin, STDIN_FILENO);	
	dup2(ogstdout, STDOUT_FILENO);
	return g_status;
}