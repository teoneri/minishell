/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:21:20 by mneri             #+#    #+#             */
/*   Updated: 2022/10/26 15:21:21 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_print_ptr(char *format, va_list args, t_state *state)
{
	const void	*k;

	if (*(format + 1) == 'p')
	{
		k = va_arg(args, void *);
		if (k != 0)
		{
			ft_p(format + 1, k);
			state -> count += (int)ft_countptrhex((uintptr_t)k) + 2;
		}
		else
		{
			write(1, "(nil)", 5);
			state -> count += 5;
		}
		format++;
		state -> state = 0;
	}
	return (format);
}
