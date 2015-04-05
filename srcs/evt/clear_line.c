/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:19:28 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:19:29 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			clear_line_evt(t_nboon *l)
{
	if (l->paste_line != NULL)
		free(l->paste_line);
	l->paste_line = nb_strdup(l->buf);
	*l->buf = '\0';
	l->b_pos = 0;
	l->b_curor = 0;
	l->b_curor_end = 0;
	l->b_len = 0;
	g_refresh_fn(l);
}
