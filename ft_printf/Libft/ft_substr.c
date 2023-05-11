/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:50:03 by mneri             #+#    #+#             */
/*   Updated: 2022/10/06 13:50:05 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	substr = (char *)malloc(sizeof(*s) * (len + 1));
	if (substr)
	{
		while (s[i])
		{
			if (i >= start && j < len)
			{
				substr[j] = s[i];
				j++;
			}
			i++;
		}
		substr[j] = '\0';
	}
	else
		return (NULL);
	return (substr);
}
