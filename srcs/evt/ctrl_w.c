/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_w.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:16 by jzak              #+#    #+#             */
/*   Updated: 2014/03/01 17:36:30 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			ctrl_w_evt(t_nboon *l)
{
	t_uint		old_pos;

	old_pos = l->b_pos;
	while (l->b_pos > 0 && l->buf[l->b_pos - 1] == ' ')
		l->b_pos--;
	while (l->b_pos > 0 && l->buf[l->b_pos - 1] != ' ')
		l->b_pos--;
	nb_memmove(&l->buf[l->b_pos], &l->buf[old_pos], l->b_len - old_pos + 1);
	l->b_len -= old_pos - l->b_pos;
	refresh_line(l);
}
