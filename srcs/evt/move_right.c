/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:20:21 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:20:22 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			move_right_evt(t_nboon *l)
{
	if (l->b_pos < l->b_len)
	{
		l->b_curor += get_display_width(get_next_char(l->buf, &l->b_pos));
		g_refresh_fn(l);
	}
}
