/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak </var/mail/jzak>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 17:39:44 by jzak              #+#    #+#             */
/*   Updated: 2014/03/01 18:49:16 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "internal.h"
#include "nboon.h"

/*
** Save history in proper order
*/
int				nb_history_save(const char *filename)
{
	int		fd;
	t_uint	i;


	if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0660)) == -1)
		return (-1);
	i = 0;
	while (i < g_history_size && g_history[i] != NULL)
	{
		write(fd, g_history[i], nb_strlen(g_history[i]));
		write(fd, "\n", 1);
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

