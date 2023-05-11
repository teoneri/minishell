/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:21:09 by mneri             #+#    #+#             */
/*   Updated: 2022/11/03 10:21:10 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_the_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*readed_line(int fd, char *stash)
{
	char	*buff;
	int		bytes_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	bytes_read = 1;
	if (!buff)
		return (NULL);
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	free (buff);
	return (stash);
}

char	*clean_stash(char *stash)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		s[j++] = stash[i++];
	if (ft_freenull(j, s, stash) == 0)
		return (NULL);
	s[j] = '\0';
	free(stash);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		return (0);
	}
	stash = readed_line(fd, stash);
	if (!stash)
		return (NULL);
	line = get_the_line(stash);
	stash = clean_stash(stash);
	return (line);
}
