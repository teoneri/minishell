/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:22:59 by mneri             #+#    #+#             */
/*   Updated: 2022/10/24 14:23:00 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_print_x(char *format, va_list args, t_state *state)
{
	unsigned int	x;

	if (*(format + 1) == 'x')
	{
		x = va_arg(args, unsigned int);
		ft_putlowhex(x);
		state -> count += ft_counthexdig(x);
		format++;
		state -> state = 0;
	}
	else if (*(format + 1) == 'X')
	{
		x = va_arg(args, unsigned int);
		ft_putuphex(x);
		state -> count += ft_counthexdig(x);
		format++;
		state -> state = 0;
	}
	return (format);
}
