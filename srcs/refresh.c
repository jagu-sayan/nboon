/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak </var/mail/jzak>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 14:04:54 by jzak              #+#    #+#             */
/*   Updated: 2014/02/27 19:00:13 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> // XXX
#include "nboon.h"

static void		s_memcpy(char *dest, t_uint *dest_idx, const char *src)
{
	int		i;

	i = 0;
	if (src == NULL)
		return ;
	while (src[i] && *dest_idx < WRITE_BUF_SIZE)
	{
		dest[*dest_idx] = src[i];
		(*dest_idx)++;
		++i;
	}
}

static void		write_vt100(int fd, const char *str, int nbr1, int nbr2)
{
	char	buf[WRITE_BUF_SIZE];
	t_uint	idx;
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	buf[0] = ESC;
	buf[1] = '[';
	if (nbr1 >= 0)
		s1 = nb_itoa((int)nbr1);
	if (nbr2 >= 0)
		s2 = nb_itoa((int)nbr2);
	idx = 2;
	s_memcpy(buf, &idx, s1);
	s_memcpy(buf, &idx, s2);
	s_memcpy(buf, &idx, str);
	buf[idx] = '\0';
	write(fd, buf, idx);
	free(s1);
	free(s2);
}

void			refresh_line(t_nboon *l)
{
	write_vt100(l->fd, "G", 0, -1);
	write(l->fd, l->prompt, l->p_len),
	write(l->fd, l->buf, l->b_len);
	write_vt100(l->fd, "K", 0, -1);
	write_vt100(l->fd, "G", 0, -1);
	write_vt100(l->fd, "C", l->p_len + l->b_pos, -1);
	/* write_vt100(l->fd, "u", -1, -1); */
}

