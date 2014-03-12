/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 19:15:04 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 22:24:52 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			delete_evt(t_nboon *l)
{
	t_uint		pos;

	if (l->b_len > 0 && l->b_pos < l->b_len)
	{
		pos = l->b_pos;
		get_next_char(l->buf, &pos);
		nb_memmove(&l->buf[l->b_pos], &l->buf[pos], l->b_len - l->b_pos - 1);
		l->b_len -= (pos - l->b_pos);
		l->buf[l->b_len] = '\0';
		refresh_line(l);
	}
}
