/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:44:01 by mneri             #+#    #+#             */
/*   Updated: 2023/05/30 14:55:15 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_copy_matrix(char **str)
{
	int i;
	char	**newstr;
	i = 0;

	while(str[i])
		i++;
	newstr = malloc(sizeof(char *) * i + 1);
	i = 0;
	while(str[i])
	{
		newstr[i] = ft_strdup(str[i]);
		i++;
	}
	newstr[i + 1] = NULL;
	return (newstr);
}	
