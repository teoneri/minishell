/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:57:32 by mneri             #+#    #+#             */
/*   Updated: 2023/06/09 14:55:55 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	ft_error(int error_typ, int err)
{
	char *str;

	if(error_typ == DUPERROR)
		ft_putstr_fd("Dup error ", 2);
	if(error_typ == FORKERROR)
		ft_putstr_fd("Fork error ", 2);
	if(error_typ == CMDNOTFOUND)
		ft_putstr_fd("Command not found ", 2);
	if(error_typ == PIPERROR)
		ft_putstr_fd("Pipe error ", 2);
	if(error_typ == DIRNOTFOUND)
		ft_putstr_fd("Directory not found ", 2);
	if(error_typ == FDERROR)
		ft_putstr_fd("Unable to open file ", 2);
	str = ft_itoa(g_status);
	ft_putendl_fd(str, 2);
	free(str);
	g_status = err;
}