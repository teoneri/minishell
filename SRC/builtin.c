/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:46:37 by mneri             #+#    #+#             */
/*   Updated: 2023/06/07 14:04:15 by mneri            ###   ########.fr       */
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
	prompt->envp[i] = ft_strjoin("PWD=", currdir);
	i = ft_findenv("OLDPWD", prompt);
	if(i >= 0)
		prompt->envp[i] = ft_strjoin("OLDPWD=", oldpwd);
	else
	{
		fullold = ft_strjoin("OLDPWD=", oldpwd);
		prompt->envp = ft_extendmatrix(prompt->envp, fullold);
	}
}

int	ft_updatetohome(t_carry *prompt, int type)
{
	int i;
	char *str;
	
	i = 0;
	if(type == 1)
	{
		i = ft_findenv("HOME=", prompt);
		str = ft_strdup(&prompt->envp[i][5]);
	}	
	else if(type == 0)
	{
		i = ft_findenv("OLDPWD=", prompt);
		str = ft_strdup(&prompt->envp[i][7]);
	}	
	if(i != -1)
	{
		chdir(str);
		free(str);
		return 1;
	}
	free(str);
	return 0;
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
		ft_updatetohome(prompt, 1);
		ft_updatepwd(currdir, prompt, fullold, oldpwd);
	}
	else if(ft_strchr(stor->whole_cmd[1], '-'))
	{
		if(ft_updatetohome(prompt, 0))
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