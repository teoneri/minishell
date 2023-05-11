/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helphex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:19:13 by mneri             #+#    #+#             */
/*   Updated: 2022/10/25 11:19:14 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_hlx(unsigned int temp, unsigned int n, char *str, int len)
{
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			str[len-- - 1] = temp + 48;
		else
			str[len-- - 1] = temp + 87;
		n = n / 16;
	}
	return (str);
}

char	*ft_hux(unsigned int temp, unsigned int n, char *str, int len)
{
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			str[len-- - 1] = temp + 48;
		else
			str[len-- - 1] = temp + 55;
		n = n / 16;
	}
	return (str);
}

char	*ft_hpx(int temp, uintptr_t n, char *str, uintptr_t len)
{
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			str[len-- - 1] = temp + 48;
		else
			str[len-- - 1] = temp + 87;
		n = n / 16;
	}
	return (str);
}
