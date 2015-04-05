/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:20:13 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:20:14 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			move_left_evt(t_nboon *l)
{
	if (l->b_pos > 0)
	{
		l->b_curor -= get_display_width(get_prev_char(l->buf, &l->b_pos));
		g_refresh_fn(l);
	}
}
