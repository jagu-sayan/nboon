/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:20:39 by jzak              #+#    #+#             */
/*   Updated: 2014/03/27 19:44:59 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void			paste_line_evt(t_nboon *l)
{
	int		size;

	if (l->paste_line != NULL)
	{
		size = (int)nb_strlen(l->paste_line);
		if (l->b_len + size < LINE_BUF_SIZE)
			insert_utf8(l, l->paste_line, size);
	}
}
