/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:04:11 by jzak              #+#    #+#             */
/*   Updated: 2014/02/28 10:23:48 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "nboon.h"

static char		**history = NULL;
static size_t	history_size = 0;
static t_uint	history_idx = 0;

/*
** nb_history_set_max_size MUST be call before other nb_history_* function
*/
int				nb_history_set_max_size(size_t size)
{
	t_uint		i;

	if (history == NULL)
	{
		history = (char**)malloc(sizeof(*history) * (size));
		if (history == NULL)
			return (-1);
		i = 0;
		while (i < size)
		{
			history[i] = NULL;
			++i;
		}
	}
	return (0);
}

int				nb_history_add(const char *line)
{
	char	*cpy;

	if (history_size == 0)
		return (0);
	if (history == NULL)
		nb_history_set_max_size(HISTORY_SIZE);
	if ((cpy = nb_strdup(line)) == NULL)
		return (-1);
	if (history_idx == history_size)
		history_idx = 0;
	if (history[history_idx] != NULL)
		free(history[history_idx]);
	history[history_idx] = cpy;
	history_idx++;
	return (0);
}

int				nb_history_save(const char *filename)
{
	int		fd;
	t_uint	i;

	if ((fd = open(filename, O_RDONLY | O_TRUNC | O_CREAT, 0660)) == -1)
		return (-1);
	i = 0;
	while (i < history_idx)
	{
		write(fd, history[i], nb_strlen(history[i]));
		++i;
	}
	close(fd);
	return (0);
}

static char		*nb_get_next_line(int fd)
{
	static char		buf[LINE_BUF_SIZE];
	t_uint			i;

	i = 0;
	while (i < LINE_BUF_SIZE && read(fd, &buf[i], 1) == 1)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			return (buf);
		}
		++i;
	}
	return (NULL);
}

int				nb_history_load(const char *filename)
{
	int		fd;
	char	*line;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	while ((line = nb_get_next_line(fd)) != NULL)
		nb_history_add(line);
	close(fd);
	return (0);
}
