/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:30:17 by mneri             #+#    #+#             */
/*   Updated: 2022/10/20 10:30:19 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

unsigned int	ft_counthexdig(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		n = n / 16;
		count ++;
	}
	return (count);
}

uintptr_t	ft_countptrhex(uintptr_t n )
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

unsigned int	ft_putuphex(unsigned int n)
{
	int				i;
	unsigned int	temp;
	char			*str;
	int				len;

	len = ft_counthexdig(n);
	str = ft_calloc(1, len + 1);
	i = 0;
	temp = 0;
	if (n == 0)
		ft_putchar_fd('0', 1);
	else
		str = ft_hux(temp, n, str, len);
	while (str[i] && i < len)
		ft_putchar_fd(str[i++], 1);
	free(str);
	return (len + 1);
}

unsigned int	ft_putlowhex(unsigned int n)
{
	int				i;
	unsigned int	temp;
	char			*str;
	int				len;

	len = ft_counthexdig(n);
	str = ft_calloc(1, len + 1);
	i = 0;
	temp = 0;
	if (n == 0)
		ft_putchar_fd('0', 1);
	else
		str = ft_hlx(temp, n, str, len);
	while (str[i] && i < len)
		ft_putchar_fd(str[i++], 1);
	free(str);
	return (len + 1);
}

unsigned int	ft_putuinptr(uintptr_t n)
{
	int			i;
	uintptr_t	temp;
	char		*str;
	uintptr_t	len;

	len = ft_countptrhex(n);
	str = malloc(sizeof(char) * len);
	i = 0;
	temp = 0;
	if (n == 0)
		ft_putchar_fd('0', 1);
	else
		str = ft_hpx(temp, n, str, len);
	while (i < len)
		ft_putchar_fd(str[i++], 1);
	free(str);
	return (len);
}
