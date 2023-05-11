/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:38:01 by mneri             #+#    #+#             */
/*   Updated: 2022/10/24 14:38:03 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_print_cs(char *format, va_list args, t_state *state)
{
	int			ch;
	const char	*s;

	if (*(format + 1) == 'c')
	{
		ch = va_arg(args, int);
		ft_putchar_fd(ch, 1);
		state -> count++;
		format++;
		state->state = 0;
	}
	else if (*(format + 1) == 's')
	{
		s = va_arg(args, const char *);
		if (s == NULL || s == 0)
			s = "(null)";
		while (*s)
		{
			ft_putchar_fd(*s++, 1);
			state -> count++;
		}
		state -> state = 0;
		format++;
	}
	return (format);
}
