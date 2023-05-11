/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pcent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:21:39 by mneri             #+#    #+#             */
/*   Updated: 2022/10/26 15:21:40 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_print_pcent(char *format, va_list args, t_state *state)
{
	const void	*k;

	if (*(format + 1) == '%')
	{
		ft_putchar_fd('%', 1);
		state -> count++;
		format ++;
		state -> state = 0;
	}
	return (format);
}
