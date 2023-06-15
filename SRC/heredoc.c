/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:34:17 by lfai              #+#    #+#             */
/*   Updated: 2023/06/14 13:10:01 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief this ft initializes the heredoc and writes
 * the content in fd[1] to be then executed by
 * next command
 * @param stor
 * @return
 */
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
		perror("heredoc duperror");
	return (fd[0]);
}
