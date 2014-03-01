/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:04:11 by jzak              #+#    #+#             */
/*   Updated: 2014/03/01 18:48:58 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "internal.h"

char			**g_history = NULL;
size_t			g_history_size = 0;
t_uint			g_history_idx = 0;

/*
** nb_history_set_max_size MUST be call before other nb_history_* function
*/
int				nb_history_init(size_t max_size)
{
	t_uint		i;

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

void			nb_history_next(void)
{

}

void			nb_history_prev(void)
{

}

int				nb_history_add(const char *line)
{
	char	*cpy;

	if (g_history_size == 0)
		return (0);
	if (g_history == NULL)
		nb_history_init(LINE_BUF_SIZE);
	if ((cpy = nb_strdup(line)) == NULL)
		return (-1);
	if (g_history_idx == g_history_size)
		g_history_idx = 0;
	if (g_history[g_history_idx] != NULL)
		free(g_history[g_history_idx]);
	g_history[g_history_idx] = cpy;
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
}
