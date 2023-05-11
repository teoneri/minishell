/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:55:36 by mneri             #+#    #+#             */
/*   Updated: 2022/07/21 15:55:38 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (dest[j] != '\0' && j < size)
		j++;
	while (src[i] != '\0' && (i + j + 1) < size)
	{
		dest[i + j] = src[i];
		i++;
	}
	if (j < size)
		dest[i + j] = '\0';
	return (ft_strlen(src) + j);
}
