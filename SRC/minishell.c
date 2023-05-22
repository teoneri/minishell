/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:29 by mneri             #+#    #+#             */
/*   Updated: 2023/05/22 15:04:12 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_path(char *env, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*tmp;

	paths = ft_split(env, ':');
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
	return (NULL);
}

void	ft_exec(char *av, char *path, char **env)
{
	char	*path_cmd;
	char	**cmd;

	cmd = ft_pipe_split(av, ' ');
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	path_cmd = ft_path(path, cmd[0]);
	if (!path)
	{
		ft_freepath(cmd);
		free(path_cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path_cmd, cmd, env) < 0)
		exit(EXIT_FAILURE);
	free(path_cmd);
	ft_freepath(cmd);
}

// void	child_pipe(char *line, char *path, char **env)
// {
// 	int	id;
// 	int pipex[2];
// 	pipe(pipex);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(pipex[0]);
// 		if (dup2(pipex[1], 1) < 0)
// 			ft_error(4);
// 		ft_exec(line, path, env);
// 	}
// 	else
// 	{
// 		wait(&id);
// 		close(pipex[1]);
// 		if (dup2(pipex[0], 0) < 0)
// 			ft_error(4);
// 	}
// }


void	child_pro(char *line, char *path, char **env)
{
	pid_t pid;

	pid = fork();
	if(pid == 0)
	{
		ft_exec(line, path, env);
	}
	else
		wait(&pid);
}

// int	ft_check_pipe(line);
// {
// 	int i;

// 	i = 0;
// 	while(line[i] != '\0')
// 	{
// 		if(line[i] == '|')
// 			return(0);
// 	}
// 	return (1);
// }

void	analyse_line(char *line)
{
	char **cmd;

	
	// if(ft_check_pipe(line) == 0)
	// {

	// }
	cmd = ft_pipe_split(line, ' ');
	if(ft_strcmp(cmd[0], "cd") == 0)
	{
		chdir(cmd[1]);
	}
}

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
//   	(void)av;
// 	char *line;
// 	char *path;
// 	path = getenv("PATH");
// 		while(1)
// 		{
// 			line = readline("\e[31m minishell> \e[34m");
// 			add_history(line);
// 			analyse_line(line);
// 			child_pro(line, path, env);
// 			free(line);
// 		}
// }

int main()
{
	char s[]= "'<Makefile'| 'cat' echo \"$PWD 'hola'\" ~/src 'tr' -d >outfile $TERM_PROGRAM";
	char **s1;
	s1 = ft_cmdtrim(s, ' ');
	s1 = ft_expander(s1);
	s1 = ft_cmdsubsplit(s1);
	int i = 0;
	while(i < 11)
	{
		printf("%s\n", s1[i]);
		i++;
}
}
