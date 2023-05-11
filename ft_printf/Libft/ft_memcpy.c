/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:29:27 by mneri             #+#    #+#             */
/*   Updated: 2022/10/04 12:29:28 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char	*char_dest;
	unsigned char	*char_src;

	char_dest = dest;
	char_src = src;
	if (!dest && !src)
		return (0);
	while (n > 0)
	{
		*char_dest = *char_src;
		char_dest++;
		char_src++;
		n--;
	}
	return (dest);
}
