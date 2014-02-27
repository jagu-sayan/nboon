/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:04:11 by jzak              #+#    #+#             */
/*   Updated: 2014/02/26 16:50:35 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int		history_len = 0;
char			**history = NULL;

int			nb_history_add(const char *str)
{

	return (0);
}

int			nb_history_save(const char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	return (0);
}

int			nb_history_load(const char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	else
	{
	
	}
	return (0);
}


