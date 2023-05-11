/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:19:36 by mneri             #+#    #+#             */
/*   Updated: 2022/10/11 12:19:38 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	howbig(long long int n)
{
	long long int	result;

	result = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		result += 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		result += 1;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*digit;
	unsigned int	nbr;

	i = howbig(n);
	digit = malloc(sizeof(char) * (i + 1));
	if (!digit)
		return (NULL);
	if (n < 0)
	{
		digit[0] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr == 0)
		digit[0] = '0';
	while (nbr != 0)
	{
		digit[i-- - 1] = (nbr % 10) + '0';
		nbr /= 10;
	}
	digit[howbig(n)] = '\0';
	return (digit);
}
