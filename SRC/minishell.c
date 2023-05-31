/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teo <teo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:15:29 by mneri             #+#    #+#             */
/*   Updated: 2023/05/31 17:34:10 by teo              ###   ########.fr       */
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

void	analyse_line(char *line, t_carry *prompt)
{
	char **s1;
	
	s1 = NULL;
	if(ft_strlen(line) != 0)
	{
		s1 = ft_cmdtrim(line, ' ');
		s1 = ft_expander(s1, prompt);
		s1 = ft_cmdsubsplit(s1);
		prompt->cmd = NULL;
		prompt->cmd = ft_fillnode(s1, prompt->cmd);
		prompt->cmd = ft_exec(prompt->cmd, prompt);
		ft_freematrix(s1);
		ft_freecontent(prompt->cmd);
	}
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
		line = readline("\e[31m minishell> \e[34m");
		add_history(line);
		analyse_line(line, prompt);
		free(line);
	}
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



// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
//   	(void)av;
// 	// char s[]= "<Makefile cat| echo \"$PWD 'hola'\" ~/src| 'tr' -d / >outfile";
// 	// char s[]= "echo \"hello      there\" how are 'you 'doing? $USER |wc -l >outfile";
// 	char s[]= "ls -l Makefile";
// 	char **s1;
// 	t_carry	*prompt;
// 	prompt = (t_carry *)malloc(sizeof(t_carry)); // Allocate memory for prompt
// 	s1 = ft_cmdtrim(s, ' ');
// 	s1 = ft_expander(s1);
// 	s1 = ft_cmdsubsplit(s1);
// 	prompt->cmd = ft_fillnode(s1);
// 	ft_exec( prompt->cmd, env);
// 	printPrompt(prompt->cmd);
	
// // 	int i = 0;
// // 	while(i < 11)
// // 	{
// // 		printf("%s\n", s1[i]);
// // 		i++;
// // }
// }
