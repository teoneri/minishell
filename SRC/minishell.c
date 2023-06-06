/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:29 by mneri             #+#    #+#             */
/*   Updated: 2023/06/06 19:58:55 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

void	ft_freestor(t_store *stor)
{
	free(stor->whole_cmd);
	free(stor->whole_path);
	free(stor);
}

void	ft_freecontent(t_list *cmd)
{
	t_list *current;
	while (cmd != NULL)
	{
		current = cmd;
		ft_freestor(cmd->content);
		cmd = cmd->next;
		free(current);
	}
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
		g_status = ft_exec(prompt->cmd, prompt);
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
	exit(g_status);
}