/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:46:37 by mneri             #+#    #+#             */
/*   Updated: 2023/05/30 15:36:53 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_addvar(t_store *stor, char **env)
{
	char *str = ft_strdup(stor->whole_cmd[1]);
	
	env = ft_extendmatrix(env, str);
	return (env);
}

char **ft_repvar(t_store *stor, char **env)
{
	int i;
	int varlen;

	varlen = (int)ft_strlen(stor->whole_cmd[1]);
	i = 0;
	while(!ft_strncmp(env[i], stor->whole_cmd[1], varlen))
		i++;
	env[i] = ft_strjoin(stor->whole_cmd[1], "=");
	return(env);
}

void	ft_export(t_store *stor, t_carry *prompt)
{
	if(getenv(stor->whole_cmd[1]))
	{
		prompt->envp = ft_repvar(stor, prompt->envp);
	}
	else
	{
		prompt->envp = ft_addvar(stor, prompt->envp);
	}
}