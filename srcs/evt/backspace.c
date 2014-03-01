/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:03 by jzak              #+#    #+#             */
/*   Updated: 2014/03/01 17:35:56 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			backspace_evt(t_nboon *l)
{
	size_t		n;

	n = l->b_len - l->b_pos;
	if (l->b_pos > 0 && l->b_len > 0)
	{
		nb_memmove(&l->buf[l->b_pos - 1], &l->buf[l->b_pos], n);
		l->b_pos--;
		l->b_len--;
		l->buf[l->b_len] = '\0';
		refresh_line(l);
	}
}
