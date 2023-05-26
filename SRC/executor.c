/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:56 by mneri             #+#    #+#             */
/*   Updated: 2023/05/26 17:56:31 by mneri            ###   ########.fr       */
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

void	ft_exec_cmd(t_store *stor, char **env)
{
	int id;
	
	id = fork();
	
	if(id == 0)
	{
		if (execve(stor->whole_path, stor->whole_cmd, env) < 0)
			perror("exec eror");
	}
	else
		wait(&id);
}


void	pipe_ex_child(t_store *stor, int fd[2], char **env)
{
	int	id;

	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) < 0)
			perror("dup eror");
		if (execve(stor->whole_path, stor->whole_cmd, env) < 0)
			perror("exec eror");
	}
	else
	{
		wait(&id);
		close(fd[1]);
		if (dup2(fd[0], 0) < 0)
			perror("dup eror");

	}
}


void	ft_exec(t_list *cmd, char **env)
{
	int fd[2];
	t_store *stor;

	stor = cmd->content;
	if(stor->infile != 0)
	{
		if (dup2(stor->infile, STDIN_FILENO) < 0)
			perror("dup eror");
	}	
	if(ft_checkpipe(cmd))
	{
		while(cmd->next != NULL)
		{
			pipe_ex_child(stor, fd, env);
			cmd = cmd->next;
			stor = cmd->content;
		}
		if(dup2(stor->outfile, 1) < 0)
			perror("dup eror");
		ft_exec_cmd(stor, env);
	}
	else
	{
		if(stor->outfile != 1)
		{
			if (dup2(stor->outfile, STDOUT_FILENO) < 0)
				perror("dup eror");
		}
		ft_exec_cmd(stor, env);
	}
}