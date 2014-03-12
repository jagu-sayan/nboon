/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:15 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 22:59:36 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			ctrl_e_evt(t_nboon *l)
{
	while (l->b_pos < l->b_len)
		l->b_curor += get_display_width(get_next_char(l->buf, &l->b_pos));
	refresh_line(l);
}
