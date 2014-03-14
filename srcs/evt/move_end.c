/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 16:00:30 by jzak              #+#    #+#             */
/*   Updated: 2014/03/14 16:02:06 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			move_end_evt(t_nboon *l)
{
	while (l->b_pos < l->b_len)
		l->b_curor += get_display_width(get_next_char(l->buf, &l->b_pos));
	refresh_line(l);
}
