/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extendmatrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:36:40 by mneri             #+#    #+#             */
/*   Updated: 2023/06/12 15:52:39 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_extendmatrix(char **mx, char *str)
{
	int		len;
	int		i;
	char	**ex_mx;

	len = ft_matrixlen(mx);
	i = 0;
	ex_mx = malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		ex_mx[i] = ft_strdup(mx[i]);
		i++;
	}
	ex_mx[len] = ft_strdup(str);
	ex_mx[len + 1] = NULL;
	ft_freematrix(mx);
	return (ex_mx);
}
