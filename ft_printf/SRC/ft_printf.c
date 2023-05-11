/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:52:14 by mneri             #+#    #+#             */
/*   Updated: 2022/10/18 10:52:15 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_state	*state;
	char	*c;
	int		count;

	va_start(args, format);
	c = (char *) format;
	state = (t_state *)malloc(sizeof(t_state));
	state -> state = 0;
	state -> count = 0;
	while (*c)
	{
		if (state ->state == 0)
			ft_printstate0(c, state);
		if (state -> state == 1)
			c = ft_printstate1(c, args, state);
		c++;
	}
	count = state->count;
	free(state);
	va_end(args);
	return (count);
}
