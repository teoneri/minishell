/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:33:37 by mneri             #+#    #+#             */
/*   Updated: 2023/05/30 14:46:29 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matrixlen(char **mx)
{
	int i;

	i = 0;

	while(mx[i] != NULL)
		i++;
	return (i);
}