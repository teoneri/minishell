/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_diu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:35:48 by mneri             #+#    #+#             */
/*   Updated: 2022/10/24 14:35:50 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_print_diu(char *format, va_list args, t_state *state)
{
	int				d;
	unsigned int	u;

	if (*(format + 1) == 'd' || *(format + 1) == 'i')
	{
		d = va_arg(args, int);
		ft_putnbr_fd(d, 1);
		state -> count += ft_countdigits(d);
		format ++;
		state -> state = 0;
	}
	else if (*(format + 1) == 'u')
	{
		u = va_arg(args, unsigned int);
		ft_putunsignednbr(u, 1);
		state -> count += ft_countdigits(u);
		format++;
		state -> state = 0;
	}
	return (format);
}
