/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:19:48 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:19:50 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			delete_evt(t_nboon *l)
{
	t_uint		pos;

	if (l->b_len > 0 && l->b_pos < l->b_len)
	{
		pos = l->b_pos;
		l->b_curor_end -= get_display_width(get_next_char(l->buf, &pos));
		nb_memmove(&l->buf[l->b_pos], &l->buf[pos], l->b_len - l->b_pos - 1);
		l->b_len -= (pos - l->b_pos);
		l->buf[l->b_len] = '\0';
		g_refresh_fn(l);
	}
}
