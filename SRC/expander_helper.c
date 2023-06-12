/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:18:08 by lfai              #+#    #+#             */
/*   Updated: 2023/06/12 12:53:00 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expjoin(char *var, char *envar, char *usrvar)
{
	char	*str;
	int		i;
	int		size;
	int		j;

	size = ft_strlen(envar) - (ft_strlen(var));
	str = malloc(sizeof(char) * size + 1);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (var[j] == '$')
		{
			j += ft_strlen(usrvar) + 1;
		}
		str[i] = envar[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(usrvar);
	free(envar);
	free(var);
	return (str);
}

int	ft_findenv(char*usrvar, t_carry *prompt)
{
	int	i;

	i = 0;
	while (prompt->envp[i])
	{
		if (!ft_strncmp(prompt->envp[i], usrvar, \
			ft_findchar(prompt->envp[i], '=')))
			return (i);
		i++;
	}
	return (-1);
}
