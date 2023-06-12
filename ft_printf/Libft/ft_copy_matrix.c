/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:53:03 by lfai              #+#    #+#             */
/*   Updated: 2023/06/12 15:53:06 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_copy_matrix(char **str)
{
	int		i;
	char	**newstr;

	i = 0;
	while (str[i])
		i++;
	newstr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		newstr[i] = ft_strdup(str[i]);
		i++;
	}
	newstr[i] = NULL;
	return (newstr);
}
