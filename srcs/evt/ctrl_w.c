/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_w.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:16 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 23:10:30 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			ctrl_w_evt(t_nboon *l)
{
	t_uint		old_pos;
	t_utf8		c;

	old_pos = l->b_pos;
	c = 32;
	while (l->b_pos > 0 && (c == ' ' || c == '\t'))
	{
		c = get_prev_char(l->buf, &l->b_pos);
		l->b_curor -= get_display_width(c);
	}
	c = 0;
	while (l->b_pos > 0 && (c != ' ' && c != '\t'))
	{
		c = get_prev_char(l->buf, &l->b_pos);
		l->b_curor -= get_display_width(c);
	}
	nb_memmove(&l->buf[l->b_pos], &l->buf[old_pos], l->b_len - old_pos + 1);
	l->b_len -= old_pos - l->b_pos;
	refresh_line(l);
}
