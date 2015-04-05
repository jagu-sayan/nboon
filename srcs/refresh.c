/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:24:43 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 15:24:58 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "internal.h"
#include "nboon.h"

t_refresh_fn	g_refresh_fn = nb_refresh_single_line;
static t_size	g_size;

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

void			nb_refresh_size(int sig)
{
	if (ioctl(1, TIOCGWINSZ, &g_size) == -1 || g_size.ws_col == 0)
		g_size.ws_col = 80;
	if (sig != 0)
	{
		nb_clear_screen();
		write(STDOUT_FILENO, "\x1b[5n", 4);
	}
}

void			nb_refresh_multi_line(t_nboon *l)
{
	t_uint	is_end;
	t_uint	rows;
	t_uint	cols;
	t_uint	pos;

	is_end = (l->p_cursor + l->b_curor_end) % g_size.ws_col;
	cols = (l->p_cursor + l->b_curor) % g_size.ws_col + 1;
	rows = (l->p_cursor + l->b_curor_end) / g_size.ws_col;
	pos = ((l->p_cursor + l->b_curor) / g_size.ws_col);
	if (l->nbr_rows > 0)
		write_vt100(l->fd, "A", l->nbr_rows, -1);
	write(l->fd, "\x1b[0G\x1b[J", 7);
	write(l->fd, l->prompt, l->p_len);
	write(l->fd, l->buf, l->b_len);
	if (rows - pos > 0)
		write_vt100(l->fd, "A", rows - pos, -1);
	if (is_end == 0 && l->b_len != 0)
		write(l->fd, "\x1b[0B", 4);
	write_vt100(l->fd, "G", cols, -1);
	l->nbr_rows = pos;
}

void			nb_refresh_single_line(t_nboon *l)
{
	t_uint	cursor;
	t_uint	end;
	t_uint	idx;
	t_uint	len;
	t_utf8	c;

	cursor = l->b_curor;
	idx = 0;
	while (l->p_cursor + cursor >= g_size.ws_col)
		cursor -= get_display_width(get_next_char(l->buf, &idx));
	len = 0;
	end = 0;
	c = 1;
	while (c != 0 && end < g_size.ws_col - l->p_cursor - 1)
	{
		c = get_next_char(l->buf + idx, &len);
		end += get_display_width(c);
	}
	write(l->fd, "\x1b[0G", 4);
	write(l->fd, l->prompt, l->p_len);
	write(l->fd, l->buf + idx, len);
	write(l->fd, "\x1b[0K\x1b[0G", 8);
	write_vt100(l->fd, "G", l->p_cursor + cursor + 1, -1);
}
