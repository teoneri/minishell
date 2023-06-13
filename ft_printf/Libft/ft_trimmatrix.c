/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimmatrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:58:14 by mneri             #+#    #+#             */
/*   Updated: 2023/06/12 15:58:40 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_trimmatrix(char **mx, int pos)
{
	char	**str;
	int		i;
	int		j;
	int		len;

	len = ft_matrixlen(mx) - 1;
	str = malloc(sizeof(char *) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (mx[i])
	{
		if (i != pos)
		{
			str[j] = ft_strdup(mx[i]);
			j++;
		}
		i++;
	}
	ft_freematrix(mx);
	str[j] = NULL;
	return (str);
}
