/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:13:23 by mneri             #+#    #+#             */
/*   Updated: 2022/10/27 12:13:25 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_print_hash(char *format, va_list args, t_state *state)
{
	unsigned int	x;

	x = va_arg(args, unsigned int);
	if (*(format + 1) == '#' && x != 0)
	{
		if (*(format + 2) == 'x')
			write(1, "0x", 2);
		else if (*(format + 2) == 'X')
			write(1, "0X", 2);
		state -> count += 2;
	}
	if (*(format + 2) == 'x')
	{
		ft_putlowhex(x);
		state -> count += ft_counthexdig(x);
		format += 2;
	}
	else if (*(format + 2) == 'X')
	{
		ft_putuphex(x);
		state -> count += ft_counthexdig(x);
		format += 2;
	}
	state -> state = 0;
	return (format);
}
