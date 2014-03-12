/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:15 by jzak              #+#    #+#             */
/*   Updated: 2014/03/11 14:37:29 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static size_t	ft_strlen_utf8(const char *s)
{
	size_t		i;

	i = 0;
	while (*s)
	{
		if ((*s & 0xc0) != 0x80)
		{
			switch (0xF0 & *s)
			{
				case 0xE0:
					i += 2;
					break;
				default:
					++i;
					break;
			}
		}
		++s;
	}
	return (i);
}

void			ctrl_e_evt(t_nboon *l)
{
	l->b_pos = l->b_len;
	l->b_curor = ft_strlen_utf8(l->buf);
	refresh_line(l);
}
