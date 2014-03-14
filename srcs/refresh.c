/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 02:59:30 by jzak              #+#    #+#             */
/*   Updated: 2014/03/14 19:39:28 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "internal.h"

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
	buf[0] = ESCAPE;
	buf[1] = '[';
	if (nbr1 >= 0)
		s1 = nb_itoa((int)nbr1);
	if (nbr2 >= 0)
		s2 = nb_itoa((int)nbr2);
	idx = 2;
	s_memcpy(buf, &idx, s1);
	if (nbr2 >= 0)
		s_memcpy(buf, &idx, ";");
	s_memcpy(buf, &idx, s2);
	s_memcpy(buf, &idx, str);
	buf[idx] = '\0';
	write(fd, buf, idx);
	free(s1);
	free(s2);
}

/* #include <fcntl.h> */
/* static int	fd = -1; */
void			refresh_line(t_nboon *l)
{
	t_uint	rows;
	t_uint	cols;
	t_uint	i;

	/* if (fd == -1) */
	/* 	fd = open("log", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); */
	rows = (l->p_len + l->b_curor) / l->cols;
	cols = (l->p_len + l->b_curor) % l->cols;
	/* dprintf(fd, "rows  : %d\n", rows); */
	/* dprintf(fd, "cols  : %d\n", cols); */
	i = 0;
	if (i++ < l->rows - rows)
		write_vt100(l->fd, "B", l->rows - rows, -1);
	i = 0;
	while (i++ < rows)
		write(l->fd, "\x1b[0G\x1b[0K\x1b[1A", 12);
	write(l->fd, "\x1b[0G\x1b[0K", 8);
	write(l->fd, l->prompt, l->p_len);
	write(l->fd, l->buf, l->b_len);
	if ((l->b_len + l->p_len) % l->cols == 0)
	{
		write(l->fd, "\n", 1);
		l->rows++;
	}
	if (l->rows - rows > 0)
		write_vt100(l->fd, "A", l->rows -rows, -1);
	write_vt100(l->fd, "G", 0, -1);
	write_vt100(l->fd, "C", (l->b_curor + l->p_len) % l->cols, -1);
}
