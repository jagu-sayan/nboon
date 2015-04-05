/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:19:54 by jzak              #+#    #+#             */
/*   Updated: 2014/03/27 19:46:41 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "internal.h"
#include "nboon.h"

static void		reset_line(t_nboon *l, const char *buf)
{
	l->b_curor = 0;
	l->b_pos = 0;
	l->b_len = nb_strlen(buf);
	l->b_curor_end = get_str_display_width(buf);
	nb_strncpy(l->buf, buf, LINE_BUF_SIZE - 1);
	l->buf[l->b_len] = '\0';
}

static void		update_line(const char *line)
{
	char	*cpy;

	if (g_history[g_history_pos] == NULL
			|| nb_strcmp(g_history[g_history_pos], line) == 0)
		return ;
	if ((cpy = nb_strdup(line)) == NULL)
		return ;
	free(g_history[g_history_pos]);
	g_history[g_history_pos] = cpy;
}

void			history_next_evt(t_nboon *l, int cmd)
{
	int				status;

	if (l->save_line != NULL)
		update_line(l->buf);
	status = (cmd == NB_HISTORY_NEXT) ? nb_history_next() : nb_history_prev();
	if (status && g_history[g_history_pos] != NULL)
	{
		if (l->save_line == NULL)
		{
			l->save_line = nb_strdup(l->buf);
			nb_history_next();
		}
		reset_line(l, g_history[g_history_pos]);
	}
	else if (l->save_line != NULL && cmd == NB_HISTORY_NEXT)
	{
		reset_line(l, l->save_line);
		free(l->save_line);
		l->save_line = NULL;
	}
	else
		write(STDERR_FILENO, "\x7", 1);
	move_end_evt(l);
}
