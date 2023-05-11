/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstate1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:50:43 by mneri             #+#    #+#             */
/*   Updated: 2022/10/26 15:50:44 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_printstate1(char *c, va_list args, t_state *state)
{
	if (*(c + 1) == 'c' || (*(c + 1) == 's'))
		c = ft_print_cs(c, args, state);
	else if (*(c + 1) == 'd' || *(c + 1) == 'i' || (*(c + 1) == 'u'))
		c = ft_print_diu(c, args, state);
	else if (*(c + 1) == 'x' || *(c + 1) == 'X')
		c = ft_print_x(c, args, state);
	else if (*(c + 1) == 'p')
		c = ft_print_ptr(c, args, state);
	else if (*(c + 1) == '%')
		c = ft_print_pcent(c, args, state);
	else if (*(c + 1) == '#')
		c = ft_print_hash(c, args, state);
	else if (*(c + 1) == ' ')
		c = ft_print_space(c, args, state);
	else if (*(c + 1) == '+')
		c = ft_print_plus(c, args, state);
	return (c);
}
