/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_prev_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 19:01:40 by jzak              #+#    #+#             */
/*   Updated: 2014/03/14 19:19:20 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			move_to_prev_word_evt(t_nboon *l)
{
	t_utf8		c;

	c = 32;
	while (l->b_pos > 0 && (c == ' ' || c == '\t'))
	{
		c = get_prev_char(l->buf, &l->b_pos);
		l->b_curor -= get_display_width(c);
	}
	c = 0;
	while (l->b_pos > 0 && (c != ' ' && c != '\t'))
	{
		c = get_prev_char(l->buf, &l->b_pos);
		l->b_curor -= get_display_width(c);
	}
	refresh_line(l);
}
