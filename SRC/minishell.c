/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:29 by mneri             #+#    #+#             */
/*   Updated: 2023/06/06 15:11:52 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		prompt->cmd = ft_fillnode(s1, prompt->cmd);
		ft_exec(prompt->cmd, prompt);
		ft_freematrix(s1);
	}
	return 1;
}

int main(int ac, char **av, char **env)
{
	(void)ac;
  	(void)av;
	char *line;
	t_carry	*prompt;

	prompt = (t_carry *)malloc(sizeof(t_carry));
	prompt->envp = ft_copy_matrix(env);	
	while(1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("\e[31m minishell> \e[34m");
		add_history(line);
		if(!analyse_line(line, prompt))
			break;
		free(line);
	}
	free(line);
	exit(0);
}

void printPrompt(t_list *prompt) {
    t_list *current = prompt;

    while (current != NULL) {
        t_store *store = (t_store *)current->content;

        printf("whole_cmd: ");
        if (store->whole_cmd != NULL) {
            int i = 0;
            while (store->whole_cmd[i] != NULL) {
                printf("%s ", store->whole_cmd[i]);
                i++;
            }
        }
        printf("\n");
        printf("whole_path: %s\n", store->whole_path);
        printf("infile: %d\n", store->infile);
        printf("outfile: %d\n", store->outfile);
        current = current->next;
    }
}
