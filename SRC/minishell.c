/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:29 by mneri             #+#    #+#             */
/*   Updated: 2023/06/09 18:26:00 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

void	ft_freestor(t_store *stor)
{
	if(stor->whole_cmd != NULL)
		free(stor->whole_cmd);
	if(stor->whole_path != NULL)
		free(stor->whole_path);
	free(stor);
}

// void	ft_freecontent(t_list *cmd)
// {
// 	t_list *current;
// 	while (cmd != NULL)
// 	{
// 		current = cmd;
// 		ft_freestor(cmd->content);
// 		cmd = cmd->next;
// 		free(current);
// 	}
// }

void	ft_freecontent(void *content)
{
	t_store	*node;

	node = content;
	if(node->whole_path != NULL)
		free(node->whole_path);
	if(node->whole_cmd != NULL)
		ft_freematrix(node->whole_cmd);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}

int	analyse_line(char *line, t_carry *prompt)
{
	char **s1;
	
	s1 = NULL;
	if(!line)
		return	0;
	if(ft_strlen(line) != 0)
	{
		s1 = ft_cmdtrim(line, ' ');
		s1 = ft_expander(s1, prompt);
		s1 = ft_cmdsubsplit(s1);
		prompt->cmd = NULL;
		prompt->cmd = ft_fillnode(s1, prompt->cmd, prompt);
		g_status = ft_exec(prompt->cmd, prompt, &s1);
		ft_freematrix(s1);
	}
	return 1;
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
    char *line;
    t_carry *prompt;

    prompt = (t_carry *)malloc(sizeof(t_carry));
    prompt->envp = ft_copy_matrix(env);
    while(1)
	{
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
        line = readline("\e[31m minishell> \e[34m");
        if (line == NULL)
		{
            printf("Exiting shell...\n");
            break;
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