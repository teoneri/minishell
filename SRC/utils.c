/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:18:22 by mneri             #+#    #+#             */
/*   Updated: 2023/06/13 19:28:38 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] != '\0')
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_strtrim_all(char **splt)
{
	int	i;

	i = 0;
	while (splt[i] != NULL)
	{
		if (splt[i][0] == '\'')
			splt[i] = ft_strtrim(splt[i], "\'");
		else if (splt[i][0] == '\"')
			splt[i] = ft_strtrim(splt[i], "\"");
		i++;
	}
	return (splt);
}
