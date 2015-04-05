/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:25:32 by jzak              #+#    #+#             */
/*   Updated: 2014/03/27 21:37:50 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "internal.h"

char			**g_history = NULL;
size_t			g_history_size = 0;
t_uint			g_history_idx = 0;
t_uint			g_history_pos = 0;

/*
** nb_history_set_max_size MUST be call before other nb_history_* function
*/
int				nb_history_init(size_t max_size)
{
	t_uint		i;

	if (max_size == 0)
		max_size = 1;
	if (g_history == NULL)
	{
		g_history = (char**)malloc(sizeof(*g_history) * (max_size));
		if (g_history == NULL)
			return (-1);
		i = 0;
		while (i < max_size)
		{
			g_history[i] = NULL;
			++i;
		}
	}
	g_history_size = max_size;
	return (0);
}

int				nb_history_next(void)
{
	t_uint		pos;

	pos = g_history_pos;
	if (pos >= g_history_size - 1)
		pos = 0;
	else
		++pos;
	if (pos != g_history_idx && g_history[pos] != NULL)
		g_history_pos = pos;
	else
		return (0);
	return (1);
}

int				nb_history_prev(void)
{
	t_uint		pos;

	pos = g_history_pos;
	if (pos == 0)
		pos = g_history_size - 1;
	else
		--pos;
	if (pos != g_history_idx && g_history[pos] != NULL)
		g_history_pos = pos;
	else
		return (0);
	return (1);
}

int				nb_history_add(const char *line)
{
	char	*cpy;
	int		pos;

	if (g_history_size == 0)
		return (0);
	if (g_history == NULL)
		nb_history_init(LINE_BUF_SIZE);
	pos = (g_history_idx == 0) ? g_history_size - 1 : g_history_idx - 1;
	if (g_history[pos] && nb_strcmp(g_history[pos], line) == 0)
		return (0);
	if ((cpy = nb_strdup(line)) == NULL)
		return (-1);
	if (g_history[g_history_idx] != NULL)
		free(g_history[g_history_idx]);
	g_history[g_history_idx] = cpy;
	g_history_pos = g_history_idx;
	if (g_history_idx >= g_history_size - 1)
		g_history_idx = 0;
	else
		g_history_idx++;
	return (0);
}

void			nb_history_free(void)
{
	t_uint		i;

	i = 0;
	while (i < g_history_size)
	{
		if (g_history[i] != NULL)
		{
			free(g_history[i]);
			g_history[i] = NULL;
		}
		++i;
	}
	free(g_history);
	g_history = NULL;
}
