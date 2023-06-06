/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:57:32 by mneri             #+#    #+#             */
/*   Updated: 2023/06/06 18:08:33 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	ft_error(int error_typ, int err)
{
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
	ft_putendl_fd(ft_itoa(g_status), 2);
	g_status = err;
}