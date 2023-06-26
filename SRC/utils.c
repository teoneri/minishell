/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:18:22 by mneri             #+#    #+#             */
/*   Updated: 2023/06/19 14:28:59 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] != '\0')
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

/*!
 * @brief this ft splits the string on the command line
 * removing also the quotes
 * @param splt
 * @return
 */
char	**ft_strtrim_all(char **splt)
{
	int	i;

	i = 0;
	while (splt[i] != NULL)
	{
		if (splt[i][0] == '\'')
			splt[i] = ft_strtrim(splt[i], "\'");
		else if (splt[i][0] == '\"')
		{
			splt[i] = ft_strtrim(splt[i], "\"");
		}
		i += 1;
	}
	return (splt);
}

int	ft_handlefiles(int *i, char **splt, t_store *stor)
{
	if (ft_checkquote(splt[*i]) && (ft_strchr(splt[*i], '>')
			|| !ft_strcmp(splt[*i], ">>")))
	{
		get_outfile(splt, i, stor);
		return (1);
	}
	else if (ft_checkquote(splt[*i]) && (ft_strchr(splt[*i], '<')
			|| !ft_strcmp(splt[*i], "<<")))
	{
		get_infile(splt, i, stor);
		return (1);
	}
	return (0);
}

void	welcome_msg(void)
{
	ft_printf(" \033[0;35m\
███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n \
████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n \
██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n \
██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n \
██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\n \
╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n \
                                                 by mneri and lfai\n\n");
}
