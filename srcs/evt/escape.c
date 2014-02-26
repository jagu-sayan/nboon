/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:17 by jzak              #+#    #+#             */
/*   Updated: 2014/02/26 18:41:25 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "nboon.h"

#define UP_KEY 65
#define DOWN_KEY 66
#define RIGHT_KEY 67
#define LEFT_KEY 68

static void		escape_extended(t_nboon *l)
{
	char	key[2];

	read(l->fd, &key, 2);
	if (key[0] == 126 && key[1] == 51)
	{
		if (l->len > 0 && l->pos < l->len)
		{
			nb_memmove(&l->buf[l->pos], &l->buf[l->pos + 1], l->len - l->pos - 1);
			l->len--;
			l->buf[l->len] = '\0';
			refreshLine(l);
		}
	}
}

static void		move_left(t_nboon *l)
{
	if (l->pos > 0)
	{
		l->pos--;
		refresh_line(l);
	}
}

static void		move_right(t_nboon *l)
{
	if (l->pos > 0)
	{
		l->pos--;
		refresh_line(l);
	}
}

void			escape_evt(t_nboon *l)
{
	char	key[2];

	read(l->fd, &key, 2);
	if (key[0] == 91)
	{
		if (key[1] == LEFT_KEY)
			move_left(l);
		else if (key[1] == RIGHT_KEY)
			move_right(l);
		else if (key[1] == UP_KEY)
			change_history();
		else if (key[1] == DOWN_KEY)
			change_history();
		else if (key[1] > 48 && key[1] < 55)
			escape_extended(l);
	}
}
