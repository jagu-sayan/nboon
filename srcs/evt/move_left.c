/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 19:14:41 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 22:24:42 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			move_left_evt(t_nboon *l)
{
	if (l->b_pos > 0)
	{
		l->b_curor -= get_display_width(get_prev_char(l->buf, &l->b_pos));
		refresh_line(l);
	}
}
