/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:56 by mneri             #+#    #+#             */
/*   Updated: 2023/06/15 16:26:17 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	ft_exec_cmd(t_store *stor, t_carry *prompt, char **str)
{
	pid_t	id;
	int		status;

	id = fork();
	if (id == -1)
		ft_error(FORKERROR, 1);
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(stor->whole_path, stor->whole_cmd, prompt->envp) < 0)
		{
			ft_error(CMDNOTFOUND, 127);
			ft_exit(prompt, str);
		}
	}
	else
	{
		waitpid(id, &status, 0);
		g_status = WEXITSTATUS(status);
	}
	return (g_status);
}

int	ft_checkbuiltin(t_store *stor, t_carry *prompt, char ***str)
{
	int	len;

	len = ft_strlen(stor->whole_cmd[0]);
	if (ft_strncmp(stor->whole_cmd[0], "cd", len) == 0 && len == 2)
	{
		ft_cd(stor, prompt);
		return (1);
	}
	else if (ft_strncmp(stor->whole_cmd[0], "export", len) == 0 && len == 6)
	{
		ft_export(stor, prompt);
		return (1);
	}
	else if (ft_strncmp(stor->whole_cmd[0], "unset", len) == 0 && len == 5)
	{
		ft_unset(stor, prompt);
		return (1);
	}
	else if (ft_continuebuiltin(stor, prompt, str, len) == 1)
		return (1);
	return (0);
}

void	pipe_ex_child(t_store *stor, int fd[2], t_carry *prompt, t_list *head)
{
	int	id;
	int	status;

	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			ft_error(DUPERROR, 1);
		else if (execve(stor->whole_path, stor->whole_cmd, prompt->envp) < 0)
		{
			ft_error(CMDNOTFOUND, 127);
			prompt->cmd = head;
			ft_exit(prompt, prompt->str);
		}
	}
	else
	{
		waitpid(id, &status, 0);
		g_status = WEXITSTATUS(status);
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			ft_error(DUPERROR, 1);
	}
}

t_store	*ft_handlepipe(t_carry *prompt, t_store *stor, int fd[2])
{
	t_list	*head;

	head = prompt->cmd;
	while (prompt->cmd->next != NULL)
	{
		pipe_ex_child(stor, fd, prompt, head);
		prompt->cmd = prompt->cmd->next;
		stor = prompt->cmd->content;
	}
	if (stor->outfile != STDOUT_FILENO)
	{
		if (dup2(stor->outfile, STDOUT_FILENO) < 0)
			ft_error(DUPERROR, 1);
	}
	return (stor);
}

/*!
 * @brief this ft executes the cmd or the builtin cmd, checking infile,
 * outfile and heredoc, preserving the og stdin and stdout.
 * @param cmd
 * @param prompt
 * @param str
 * @param fd
 * @return
 */
int	ft_exec(t_list *cmd, t_carry *prompt, char ***str, int fd[2])
{
	int		ogstdin;
	int		ogstdout;
	t_store	*stor;
	t_list	*head;

	head = prompt->cmd;
	stor = prompt->cmd->content;
	ogstdout = dup(STDOUT_FILENO);
	ogstdin = dup(STDIN_FILENO);
	if (stor->here_doc != NULL)
		stor->infile = ft_handlehere_doc(stor);
	if (hande_file(stor->infile, 1) != -1 && hande_file(stor->outfile, 0) != -1)
	{
		if (ft_checkpipe(cmd))
		{
			stor = ft_handlepipe(prompt, stor, fd);
			ft_exec_cmd(stor, prompt, *str);
		}
		else
			ft_continue_exec(stor, prompt, str);
	}
	ft_finish_exec(prompt, head, &ogstdin, &ogstdout);
	return (g_status);
}
