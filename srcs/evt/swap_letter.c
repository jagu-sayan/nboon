/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_letter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:20:44 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:21:42 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			swap_letter_evt(t_nboon *l)
{
	static char	swap[5] = { '\0' };
	t_uint		s1;
	t_uint		s2;
	t_utf8		c;
	int			pos;

	if (l->b_pos == 0)
		l->b_curor += get_display_width(get_next_char(l->buf, &l->b_pos));
	if (l->b_pos != 0 && l->b_pos == l->b_len)
		l->b_curor -= get_display_width(get_prev_char(l->buf, &l->b_pos));
	pos = l->b_pos;
	if ((c = get_prev_char(l->buf, &l->b_pos)) == 0)
		l->b_curor += get_display_width(get_next_char(l->buf, &l->b_pos));
	else
	{
		s1 = pos - l->b_pos;
		l->b_pos = pos;
		c = get_next_char(l->buf, &l->b_pos);
		l->b_curor += get_display_width(c);
		s2 = l->b_pos - pos;
		nb_strncpy(swap, &l->buf[pos], s2);
		nb_memmove(&l->buf[pos - s1 + s2], &l->buf[pos - s1], s1);
		nb_strncpy(&l->buf[pos - s1], swap, s2);
	}
	g_refresh_fn(l);
}
