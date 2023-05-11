/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:53:15 by mneri             #+#    #+#             */
/*   Updated: 2022/10/27 14:53:16 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_print_plus(char *format, va_list args, t_state *state)
{
	int				d;

	d = va_arg(args, int);
	if (*(format + 1) == '+')
	{
		if (d >= 0)
		{
			write(1, "+", 1);
			state->count++;
		}
		while (*(format + 1) == '+')
			format++;
		if ((*(format + 1) == 'd' || *(format + 1) == 'i'))
		{
			ft_putnbr_fd(d, 1);
			state -> count += ft_countdigits(d);
		}
		state -> state = 0;
		format ++;
	}
	return (format);
}
