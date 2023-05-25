
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

void	child_pipe(char *line, char *path, char **env)
{
	int	id;
	int pipex[2];
	pipe(pipex);
	id = fork();
	if (id == 0)
	{
		close(pipex[0]);
		if (dup2(pipex[1], 1) < 0)
			ft_error(4);
		ft_exec(line, path, env);
	}
	else
	{
		wait(&id);
		close(pipex[1]);
		if (dup2(pipex[0], 0) < 0)
			ft_error(4);
	}
}


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

int	ft_check_pipe(line);
{
	int i;

	i = 0;
	while(line[i] != '\0')
	{
		if(line[i] == '|')
			return(0);
	}
	return (1);
}
