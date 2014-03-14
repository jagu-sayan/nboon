/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nboon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 00:53:03 by jzak              #+#    #+#             */
/*   Updated: 2014/03/14 15:58:47 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>
#include "internal.h"
#include "nboon.h"

static void		insert_utf8(t_nboon *l, char *data, int size)
{
	t_uint		i;
	t_utf8		c;

	i = 0;
	c = 1;
	while (c != 0)
	{
		c = get_next_char(data, &i);
		l->b_curor += get_display_width(c);
	}
	i = 0;
	if (l->b_len != l->b_pos)
		nb_memmove(&l->buf[l->b_pos + size], &l->buf[l->b_pos], l->b_len - l->b_pos);
	while (data[i] != '\0')
	{
		l->buf[l->b_pos] = data[i];
		l->b_pos++;
		l->b_len++;
		++i;
	}
	l->buf[l->b_len] = '\0';
	refresh_line(l);
}

static int		get_columns(void)
{
	struct winsize		ws;

	if (ioctl(1, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (80);
	return (ws.ws_col);
}

static int		line_edit(t_nboon *l)
{
	char	c[LINE_BUF_SIZE] = { 0 };
	int		ret;

	write(l->fd, l->prompt, l->p_len);
	while ((ret = read(l->fd, &c, LINE_BUF_SIZE)) > 0)
	{
		c[ret] = '\0';
		if (c[0] == CTRL_D)
		{
			if (l->b_len == 0)
				return (-1);
			delete_evt(l);
		}
		else if (c[0] == CTRL_C || c[0] == ENTER || c[0] == CTRL_J)
			return (0);
		else if (execute_evt(l, c[0], &c[1]) == 0)
		{
			if (l->b_len + ret < LINE_BUF_SIZE)
				insert_utf8(l, c, ret);
			else
				return (-1);
		}
	}
	return (0);
}

/*
** The call to get_line() will block as long as the user types something
** and presses enter.
**
** The typed string is returned as a malloc() allocated string,
** so the user needs to free() it.
**/
char			*nb_get_line(const char *prompt)
{
	t_nboon		line;
	int			count;

	line.fd = STDIN_FILENO;
	line.buf[0] = '\0';
	line.b_len = 0;
	line.b_pos = 0;
	line.b_curor = 0;
	line.prompt = prompt;
	line.p_len = nb_strlen(prompt);
	line.cols = get_columns();
	line.rows = 0;
	count = -1;
	if (isatty(STDIN_FILENO) && nb_enable_raw(STDIN_FILENO) != -1)
	{
		count = line_edit(&line);
		nb_disable_raw(STDIN_FILENO);
		write(1, "\n", 1);
		if (count == -1)
			return (NULL);
	}
	else
		return (NULL);
	return (nb_strdup(line.buf));
}
