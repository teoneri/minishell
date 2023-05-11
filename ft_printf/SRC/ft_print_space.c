/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:46:48 by mneri             #+#    #+#             */
/*   Updated: 2022/10/27 12:46:49 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_print_space(char *format, va_list args, t_state *state)
{
	int				d;

	d = va_arg(args, int);
	if (*(format + 1) == ' ')
	{
		if (d >= 0)
		{
			write(1, " ", 1);
			state->count++;
		}
		while (*(format + 1) == ' ')
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
