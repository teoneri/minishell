/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignednbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:05:16 by mneri             #+#    #+#             */
/*   Updated: 2022/10/21 15:05:17 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putunsignednbr(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_putunsignednbr(n / 10, fd);
		ft_putunsignednbr(n % 10, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}
