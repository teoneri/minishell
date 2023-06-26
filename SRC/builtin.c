/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:46:37 by mneri             #+#    #+#             */
/*   Updated: 2023/06/14 14:34:06 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_updatepwd(char *cdir, t_carry *p, char *fold, char *opwd)
{
	int	i;

	i = ft_findenv("PWD", p);
	cdir = getcwd(NULL, 0);
	free(p->envp[i]);
	p->envp[i] = ft_strjoin("PWD=", cdir);
	i = ft_findenv("OLDPWD", p);
	if (i >= 0)
	{
		free(p->envp[i]);
		p->envp[i] = ft_strjoin("OLDPWD=", opwd);
	}
	else
	{
		fold = ft_strjoin("OLDPWD=", opwd);
		p->envp = ft_extendmatrix(p->envp, fold);
	}
	free(cdir);
	free(fold);
}

int	ft_updatetohome(t_carry *prompt, int type)
{
	int		i;
	char	*str;

	i = 0;
	if (type == 1)
	{
		i = ft_findenv("HOME=", prompt);
		str = ft_strdup(&prompt->envp[i][5]);
	}
	else if (type == 0)
	{
		i = ft_findenv("OLDPWD=", prompt);
		str = ft_strdup(&prompt->envp[i][7]);
	}
	if (i != -1)
	{
		chdir(str);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

void	ft_cd(t_store *stor, t_carry *prompt)
{
	char	*oldpwd;
	char	*currdir;
	char	*fullold;

	currdir = NULL;
	fullold = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!stor->whole_cmd[1] || !ft_strcmp(stor->whole_cmd[1], "~"))
	{
		ft_updatetohome(prompt, 1);
		ft_updatepwd(currdir, prompt, fullold, oldpwd);
	}
	else if (ft_strchr(stor->whole_cmd[1], '-'))
	{
		if (ft_updatetohome(prompt, 0))
			ft_updatepwd(currdir, prompt, fullold, oldpwd);
	}
	else if (chdir(stor->whole_cmd[1]) != 1)
	{
		ft_updatepwd(currdir, prompt, fullold, oldpwd);
	}
	else
		ft_error(DIRNOTFOUND, 1);
	free(oldpwd);
}

void	ft_exit(t_carry *prompt, char **str)
{
	ft_lstclear(&prompt->cmd, ft_freecontent);
	ft_freematrix(prompt->envp);
	free(prompt);
	ft_freematrix(str);
	exit(g_status);
}
