/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:17 by jzak              #+#    #+#             */
/*   Updated: 2014/03/01 18:44:01 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "internal.h"


static void		escape_extended(t_nboon *l, char evt)
{
	char	key[2];

	read(l->fd, &key, 2);
	if (evt == 51 && key[0] == DELETE)
		delete_evt(l);
}

void			delete_evt(t_nboon *l)
{
	size_t		n;

	n = l->b_len - l->b_pos - 1;
	if (l->b_len > 0 && l->b_pos < l->b_len)
	{
		nb_memmove(&l->buf[l->b_pos], &l->buf[l->b_pos + 1], n);
		l->b_len--;
		l->buf[l->b_len] = '\0';
		refresh_line(l);
	}
}

void			move_left_evt(t_nboon *l)
{
	if (l->b_pos > 0)
	{
		l->b_pos--;
		refresh_line(l);
	}
}

void			move_right_evt(t_nboon *l)
{
	if (l->b_pos < l->b_len)
	{
		l->b_pos++;
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
			move_left_evt(l);
		else if (key[1] == RIGHT_KEY)
			move_right_evt(l);
		else if (key[1] == UP_KEY)
			ctrl_p_evt(l);
		else if (key[1] == DOWN_KEY)
			ctrl_n_evt(l);
		else if (key[1] > 48 && key[1] < 55)
			escape_extended(l, key[1]);
	}
}
