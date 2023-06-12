/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:54:27 by mneri             #+#    #+#             */
/*   Updated: 2023/06/12 15:37:11 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_findvar(char*usrvar, t_carry *prompt)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (usrvar[i] != '=' && usrvar[i] != '\0')
		i++;
	str = malloc(sizeof(char) * i + 1);
	while (i-- > 0)
	{
		str[j] = usrvar[j];
		j++;
	}
	str[j] = '\0';
	i = ft_findenv(str, prompt);
	if (i >= 0)
	{
		free(str);
		return (i);
	}
	free(str);
	return (-1);
}

void	ft_export(t_store *stor, t_carry *prompt)
{
	int	i;

	i = ft_findvar(stor->whole_cmd[1], prompt);
	if ((i >= 0))
	{
		free(prompt->envp[i]);
		prompt->envp[i] = ft_strdup(stor->whole_cmd[1]);
	}
	else
	{
		if (ft_findchar(stor->whole_cmd[1], '=') >= 0)
			prompt->envp = ft_extendmatrix(prompt->envp, stor->whole_cmd[1]);
	}
}

void	ft_unset(t_store *stor, t_carry *prompt)
{
	int	i;

	i = ft_findenv(stor->whole_cmd[1], prompt);
	if (i >= 0)
	{
		prompt->envp = ft_trimmatrix(prompt->envp, i);
	}
}
