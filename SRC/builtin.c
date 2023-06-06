/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:46:37 by mneri             #+#    #+#             */
/*   Updated: 2023/06/06 20:08:59 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_findvar(char*usrvar, t_carry *prompt)
{
	int i;
	int j;
	char *str;
	
	i = 0;
	j = 0;
	while(usrvar[i] != '=' && usrvar[i] != '\0')
		i++;
	str = malloc(sizeof(char) * i + 1);
	while(i-- > 0)
	{
		str[j] = usrvar[j];
		j++;
	}
	str[j] = '\0';
	if((i = ft_findenv(str, prompt)) >= 0)
	{
		free(str);
		return i;
	}
	return -1;
}

void	ft_echo(void)
{
	char *str;

	str = ft_itoa(g_status);
	ft_printf("%s\n", str);
}


void	ft_export(t_store *stor, t_carry *prompt)
{
	int i;

	i = ft_findvar(stor->whole_cmd[1], prompt);
	if((i >= 0))
		prompt->envp[i] = ft_strdup(stor->whole_cmd[1]);

	else
	{
		if(ft_findchar(stor->whole_cmd[1], '=') >= 0)
			prompt->envp =ft_extendmatrix(prompt->envp, stor->whole_cmd[1]);
	}
}

void	ft_unset(t_store *stor, t_carry *prompt)
{
	int i;
	
	i = ft_findenv(stor->whole_cmd[1], prompt);
	if(i >= 0)
		prompt->envp = ft_trimmatrix(prompt->envp, i);
}

void ft_updatepwd(char *currdir, t_carry *prompt, char *fullold, char *oldpwd)
{
	int i;
	
	i = ft_findenv("PWD", prompt);
	currdir = getcwd(NULL, 0);
	prompt->envp[i] = ft_strdup(currdir);
	i = ft_findenv("OLDPWD", prompt);
	if(i >= 0)
		prompt->envp[i] = ft_strdup(currdir);
	else
	{
		fullold = ft_strjoin("OLDPWD=", oldpwd);
		prompt->envp = ft_extendmatrix(prompt->envp, fullold);
	}
}

void	ft_cd(t_store *stor, t_carry *prompt)
{
	char *oldpwd;
	char *currdir;
	char *fullold;
	
	currdir = NULL;
	fullold = NULL;
	oldpwd = getcwd(NULL, 0);
	if(!stor->whole_cmd[1] || ft_strchr(stor->whole_cmd[1], '~'))
	{
		chdir("~");
		ft_updatepwd(currdir, prompt, fullold, oldpwd);
	}
	else if(chdir(stor->whole_cmd[1]) != 1)
	{
		ft_updatepwd(currdir, prompt, fullold, oldpwd);
	}
	else
		ft_error(DIRNOTFOUND, 1);
}

void	ft_exit(t_carry *prompt)
{
	ft_freecontent(prompt->cmd);
	exit(0);
}