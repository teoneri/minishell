/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:34:17 by lfai              #+#    #+#             */
/*   Updated: 2023/06/13 18:53:52 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handlehere_doc(t_store *stor)
{
	int		fd[2];
	char	*line;

	pipe(fd);
	while (1)
	{
		line = readline(">");
		if (!line || \
		ft_strncmp(line, stor->here_doc, ft_strlen(stor->here_doc)) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		perror("herdoc duperror");
	return (fd[0]);
}
