/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:29 by mneri             #+#    #+#             */
/*   Updated: 2023/06/19 14:29:16 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	ft_freestor(t_store *stor)
{
	if (stor->whole_cmd != NULL)
		free(stor->whole_cmd);
	if (stor->whole_path != NULL)
		free(stor->whole_path);
	free(stor);
}

void	ft_freecontent(void *content)
{
	t_store	*node;

	node = content;
	if (node->whole_path != NULL)
		free(node->whole_path);
	if (node->whole_cmd != NULL)
		ft_freematrix(node->whole_cmd);
	if (node->here_doc != NULL)
		free(node->here_doc);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}

/*!
 * @brief this ft checks what's on the command line, parse the args on it
 * and then executes. It will also give a signal message when needed.
 * @param line command line
 * @param prompt
 * @return
 */
int	analyse_line(char *line, t_carry *prompt)
{
	int		fd[2];
	int		i;

	i = 0;
	if (!line)
		return (0);
	if (ft_checkspaces(line) && ft_strlen(line) != 0)
	{
		prompt->str = ft_cmdtrim(line, ' ');
		prompt->str = ft_expander(prompt->str, prompt);
		prompt->str = ft_cmdsubsplit(prompt->str);
		prompt->cmd = NULL;
		prompt->cmd = ft_fillnode(prompt->str, prompt->cmd, prompt, i);
		g_status = ft_exec(prompt->cmd, prompt, &prompt->str, fd);
		ft_freematrix(prompt->str);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_carry	*prompt;

	(void)ac;
	(void)av;
	prompt = (t_carry *)malloc(sizeof(t_carry));
	prompt->envp = ft_copy_matrix(env);
	welcome_msg();
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("\e[31m minishell> \e[34m");
		if (line == NULL)
		{
			printf("Exiting shell...\n");
			break ;
		}
		add_history(line);
		analyse_line(line, prompt);
		free(line);
	}
	free(line);
	ft_freematrix(prompt->envp);
	free(prompt);
	exit(g_status);
}
