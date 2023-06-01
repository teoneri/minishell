/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teo <teo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:56 by mneri             #+#    #+#             */
/*   Updated: 2023/06/01 17:14:43 by teo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int	ft_checkpipe(t_list *cmd)
{
	if(cmd->next == NULL)
		return (0);
	else
		return (1);
}

void	ft_exec_cmd(t_store *stor, t_carry *prompt, int fd[2])
{
	pid_t id;
	
	id = fork();

	if (id == 0)
	{
		if (execve(stor->whole_path, stor->whole_cmd, prompt->envp) < 0)
			perror("exec error");
	}
	else
	{
		close(fd[0]);
		close(stor->infile);
		waitpid(id, NULL, 0);
	}
}

int	ft_checkbuiltin(t_store *stor, t_carry *prompt)
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
	else if(ft_strncmp(stor->whole_cmd[0], "exit", len) == 0 && len == 4)
	{
		ft_exit(prompt);
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
			perror("dup eror");
		if(ft_checkbuiltin(stor, prompt))
			exit(0);
		else if (execve(stor->whole_path, stor->whole_cmd, prompt->envp) < 0)
			perror("exec eror");
	}
	else
	{
		wait(&id);
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			perror("dup eror");
	}
}


void	ft_handlepipe(t_list *cmd, t_carry *prompt, t_store *stor, int fd[2])
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
			perror("dup eror");
	}
	ft_exec_cmd(stor, prompt, fd);
}


t_list	*ft_exec(t_list *cmd, t_carry *prompt)
{
	int fd[2];
	t_store *stor;
	t_list *head;
	int ogstdin= dup(STDIN_FILENO);
	int ogstdout= dup(STDOUT_FILENO);
	head = cmd;
	stor = cmd->content;
	if(stor->here_doc != NULL)
		stor->infile = ft_handlehere_doc(stor);
	if(stor->infile != 0)
	{
		if (dup2(stor->infile, STDIN_FILENO) < 0)
			perror("dup eror");
	}
	if(ft_checkpipe(cmd))
		ft_handlepipe(cmd, prompt, stor, fd);
	else
	{
		if(stor->outfile != 1)
		{
			if (dup2(stor->outfile, STDOUT_FILENO) < 0)
				perror("dup eror");
		}
		if(ft_checkbuiltin(stor, prompt))
			;
		else
			ft_exec_cmd(stor, prompt, fd);
	}
	dup2(ogstdin, STDIN_FILENO);	
	dup2(ogstdout, STDOUT_FILENO);
	return(head);
}