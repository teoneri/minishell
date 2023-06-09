/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:18:08 by lfai              #+#    #+#             */
/*   Updated: 2023/06/19 13:44:37 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*ft_fixvar(char *var, char *str, char *usrvar)
{
	int		i;
	int		len;
	char	*newvar;
	int		j;
	int		k;

	k = 0;
	len = (ft_strlen(var) - ft_strlen(usrvar) - 1) + ft_strlen(str);
	newvar = malloc(sizeof(char) * len + 1);
	i = 0;
	while (var[i] != '$')
	{
		newvar[i] = var[i];
		i++;
	}
	j = ft_strlen(usrvar) + i + 1;
	while (str[k] != '\0')
		newvar[i++] = str[k++];
	while (var[j] != '\0')
		newvar[i++] = var[j++];
	newvar[i] = '\0';
	free(str);
	return (newvar);
}

char	*ft_expjoin(char *var, char *envar, char *usrvar)
{
	char	*str;
	int		i;
	int		size;
	int		j;

	size = ft_strlen(envar) - (ft_strlen(usrvar) + 1);
	str = malloc(sizeof(char) * size + 1);
	i = 0;
	j = ft_strlen(usrvar) + 1;
	while (i < size)
	{
		str[i] = envar[j];
		i++;
		j++;
	}
	str[i] = '\0';
	str = ft_fixvar(var, str, usrvar);
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

char	*ft_expand_qmark(char *var)
{
	char	*str;

	str = ft_itoa(g_status);
	free(var);
	return (str);
}
