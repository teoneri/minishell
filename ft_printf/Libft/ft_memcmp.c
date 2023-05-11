/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:46:28 by mneri             #+#    #+#             */
/*   Updated: 2022/10/05 10:46:33 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (void *) s1;
	c2 = (void *) s2;
	while (n > 0)
	{
		if (*c1 < *c2)
			return (-1);
		else if (*c1 > *c2)
			return (1);
		c1++;
		c2++;
		n--;
	}
	return (0);
}
