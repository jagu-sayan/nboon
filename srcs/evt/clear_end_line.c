/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_end_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:19:22 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:19:23 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			clear_end_line_evt(t_nboon *l)
{
	if (l->paste_line != NULL)
		free(l->paste_line);
	l->paste_line = nb_strdup(&l->buf[l->b_pos]);
	l->buf[l->b_pos] = '\0';
	l->b_curor_end = get_str_display_width(l->buf);
	l->b_len = l->b_pos;
	g_refresh_fn(l);
}
