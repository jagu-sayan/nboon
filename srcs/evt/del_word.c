/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:19:43 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:19:44 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void		del_space(t_nboon *l)
{
	t_utf8		c;

	c = 32;
	while (l->b_pos > 0 && (c == ' ' || c == '\t'))
	{
		c = get_prev_char(l->buf, &l->b_pos);
		l->b_curor -= get_display_width(c);
	}
}

void			del_word_evt(t_nboon *l)
{
	t_uint		old_pos;
	t_utf8		c;

	old_pos = l->b_pos;
	del_space(l);
	c = 0;
	while (l->b_pos > 0 && (c != ' ' && c != '\t'))
	{
		c = get_prev_char(l->buf, &l->b_pos);
		l->b_curor -= get_display_width(c);
	}
	if (l->paste_line != NULL)
		free(l->paste_line);
	l->paste_line = nb_strdup(&l->buf[l->b_pos]);
	nb_memmove(&l->buf[l->b_pos], &l->buf[old_pos], l->b_len - old_pos + 1);
	l->b_len -= old_pos - l->b_pos;
	l->b_curor_end = get_str_display_width(l->buf);
	g_refresh_fn(l);
}

void			del_path_evt(t_nboon *l)
{
	t_uint		old_pos;
	t_utf8		c;

	old_pos = l->b_pos;
	del_space(l);
	c = 0;
	while (l->b_pos > 0 && (c != ' ' && c != '\t' && c != '/'))
	{
		c = get_prev_char(l->buf, &l->b_pos);
		l->b_curor -= get_display_width(c);
	}
	if (l->paste_line != NULL)
		free(l->paste_line);
	l->paste_line = nb_strdup(&l->buf[l->b_pos]);
	nb_memmove(&l->buf[l->b_pos], &l->buf[old_pos], l->b_len - old_pos + 1);
	l->b_len -= old_pos - l->b_pos;
	l->b_curor_end = get_str_display_width(l->buf);
	g_refresh_fn(l);
}
