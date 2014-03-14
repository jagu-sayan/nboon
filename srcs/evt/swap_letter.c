/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_letter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 16:10:25 by jzak              #+#    #+#             */
/*   Updated: 2014/03/14 16:10:35 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			swap_letter_evt(t_nboon *l)
{
	char	swap;
	int		pos;

	if (l->b_pos == l->b_len)
		pos = l->b_pos - 1;
	else
		pos = l->b_pos;
	if (pos >= 1)
	{
		swap = l->buf[pos];
		l->buf[pos] = l->buf[pos - 1];
		l->buf[pos - 1] = swap;
		if (l->b_pos != l->b_len)
			l->b_pos++;
		refresh_line(l);
	}
}
