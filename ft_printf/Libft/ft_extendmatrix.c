/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extendmatrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:36:40 by mneri             #+#    #+#             */
/*   Updated: 2023/05/30 15:06:36 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char **ft_extendmatrix(char **mx, char *str)
{
	int		len;
	char	**ex_mx;
	
	len = ft_matrixlen(mx);
	ex_mx = malloc(sizeof(char *) * (len + 1));
	ex_mx = ft_copy_matrix(mx);
	ex_mx[len] = ft_strdup(str);
	ex_mx[len + 1] = NULL;
	return(ex_mx);
}