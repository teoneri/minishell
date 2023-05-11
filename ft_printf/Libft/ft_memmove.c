/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:51:14 by mneri             #+#    #+#             */
/*   Updated: 2022/10/04 12:51:17 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*char_dest;
	char	*char_src;

	char_dest = (char *)dest;
	char_src = (char *)src;
	if (char_dest > char_src)
	{
		char_dest = char_dest + n - 1;
		char_src = char_src + n - 1;
		while (n-- > 0)
		{
			*char_dest-- = *char_src--;
		}
	}
	else
	{
		while (n-- > 0)
		{
			*char_dest++ = *char_src++;
		}
	}
	return (dest);
}
