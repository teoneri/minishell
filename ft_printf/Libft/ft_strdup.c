/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:56:28 by mneri             #+#    #+#             */
/*   Updated: 2022/10/06 12:56:29 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int			len;
	char		*dups;
	int			i;

	len = ft_strlen((char *)s);
	dups = malloc(sizeof(char) * len + 1);
	if (!dups)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dups[i] = s[i];
		i++;
	}
	dups[i] = '\0';
	return (dups);
}
