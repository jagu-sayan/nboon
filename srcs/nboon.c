/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nboon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:24:31 by jzak              #+#    #+#             */
/*   Updated: 2015/04/05 13:00:47 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "internal.h"
#include "nboon.h"

static int		proccess_evt(t_nboon *l, char *c, size_t len)
{
	if (c[0] == CTRL_D)
	{
		if (l->b_len == 0)
			return (NB_EXIT);
		delete_evt(l);
	}
	else if (c[0] == ENTER || c[0] == CTRL_J)
		return (NB_SUCCESS);
	else if (c[0] == CTRL_C)
		return (NB_INTERRUPT);
	else if (c[0] == ESCAPE && c[1] == '[' && c[2] == '0' && c[3] == 'n')
		g_refresh_fn(l);
	else if (execute_evt(l, c[0], &c[1]) == 0)
	{
		if (l->b_len + len < LINE_BUF_SIZE)
			insert_utf8(l, c, len);
		else
		{
			clear_line_evt(l);
			g_nb_error = ERR_TO_LONG;
			return (NB_ERROR);
		}
	}
	return (250);
}

static int		line_edit(t_nboon *l)
{
	static char		buf[LINE_BUF_SIZE] = { 0 };
	int				ret;

	write(l->fd, l->prompt, l->p_len);
	while ((ret = read(l->fd, &buf, LINE_BUF_SIZE)) > 0 && g_nb_error == -1)
	{
		buf[ret] = '\0';
		ret = proccess_evt(l, buf, ret);
		if (ret != 250)
			return (ret);
	}
	return (NB_SUCCESS);
}

void			nb_set_refresh_callback(t_refresh_fn fn)
{
	g_refresh_fn = fn;
}

static void		init_line(t_nboon *l)
{
	l->fd = STDIN_FILENO;
	l->buf[0] = '\0';
	l->paste_line = NULL;
	l->save_line = NULL;
	l->b_len = 0;
	l->b_pos = 0;
	l->b_curor = 0;
	l->b_curor_end = 0;
}

t_nb_status		nb_get_line(const char *prompt, char **line)
{
	t_nboon		l;
	int			ret;

	if (nb_enable_raw(STDIN_FILENO) == -1)
		return (NB_ERROR);
	init_line(&l);
	l.p_cursor = get_str_display_width(prompt);
	l.p_len = expand_prompt(prompt, &l.prompt);
	l.nbr_rows = 0;
	nb_refresh_size(0);
	ret = line_edit(&l);
	nb_disable_raw(l.fd);
	free(l.prompt);
	free(l.paste_line);
	free(l.save_line);
	write(l.fd, "\n", 1);
	*line = ((ret != NB_EXIT) ? nb_strdup(l.buf) : NULL);
	return (ret);
}
