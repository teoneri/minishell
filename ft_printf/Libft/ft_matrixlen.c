/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:53:48 by lfai              #+#    #+#             */
/*   Updated: 2023/06/12 15:57:26 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matrixlen(char **mx)
{
	int	i;

	i = 0;
	while (mx[i] != NULL)
		i++;
	return (i);
}
