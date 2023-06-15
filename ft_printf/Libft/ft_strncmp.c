/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:25:22 by mneri             #+#    #+#             */
/*   Updated: 2023/06/14 14:14:22 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int		i;
	unsigned char		*t1;
	unsigned char		*t2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	i = 0;
	while ((t1[i] != '\0' || t2[i] != '\0') && i < n)
	{
		if (t1[i] == t2[i])
			i++;
		else
			return (t1[i] - t2[i]);
	}
	return (0);
}
