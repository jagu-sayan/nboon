/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:03 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 22:23:58 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "internal.h"

void			backspace_evt(t_nboon *l)
{
	if (l->b_pos > 0)
	{
		l->b_curor -= get_display_width(get_prev_char(l->buf, &l->b_pos));
		delete_evt(l);
	}
}
