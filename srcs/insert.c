/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:24:02 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 15:24:03 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			insert_utf8(t_nboon *l, char *data, int size)
{
	t_uint		i;
	t_utf8		c;
	t_uint		width;
	t_uint		pos;

	i = 0;
	c = 1;
	while (c != 0)
	{
		c = get_next_char(data, &i);
		width = get_display_width(c);
		l->b_curor += width;
		l->b_curor_end += width;
	}
	i = 0;
	pos = l->b_len - l->b_pos;
	if (l->b_len != l->b_pos)
		nb_memmove(&l->buf[l->b_pos + size], &l->buf[l->b_pos], pos);
	while (data[i] != '\0')
	{
		l->buf[l->b_pos++] = data[i++];
		l->b_len++;
	}
	l->buf[l->b_len] = '\0';
	g_refresh_fn(l);
}
