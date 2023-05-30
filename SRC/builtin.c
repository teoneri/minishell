/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:46:37 by mneri             #+#    #+#             */
/*   Updated: 2023/05/30 18:20:53 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_findvar(char*usrvar, t_carry *prompt)
{
	int i;
	int j;
	char *str;
	
	i = 0;
	j = 0;
	while(usrvar[i] != '=')
		i++;
	str = malloc(sizeof(char) * i + 1);
	while(i-- > 0)
	{
		str[j] = usrvar[j];
		j++;
	}
	str[j] = '\0';
	if((i = ft_findenv(str, prompt)) != 0)
	{
		free(str);
		return 1;
	}
	return 0;
}

void ft_repvar(t_store *stor, t_carry *prompt, int i)
{
	(void)stor;
	(void)prompt;
	(void)i;
	printf("ENTERED");
	
}

void	ft_export(t_store *stor, t_carry *prompt)
{
	int i;

	i = 0;
	if((i = ft_findvar(stor->whole_cmd[1], prompt) != 0))
		 ft_repvar(stor, prompt, i);
	else
		prompt->envp =ft_extendmatrix(prompt->envp, stor->whole_cmd[1]);
}