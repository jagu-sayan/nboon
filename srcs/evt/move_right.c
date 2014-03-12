/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 19:14:50 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 19:58:14 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			move_right_evt(t_nboon *l)
{
	if (l->b_pos < l->b_len)
	{
		l->b_curor += get_display_width(get_next_char(l->buf, &l->b_pos));
		refresh_line(l);
	}
}
