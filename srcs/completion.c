/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:21:41 by jzak              #+#    #+#             */
/*   Updated: 2014/03/27 21:12:18 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "internal.h"
#include "nboon.h"

static t_comp_fn	*g_completion_callback = NULL;

void			nb_set_completion_callback(t_comp_fn *fn)
{
	g_completion_callback = fn;
}

static char		*get_prev_word(char *buf, unsigned int pos)
{
	unsigned int	i;
	unsigned int	old_pos;
	char			*new;

	old_pos = pos;
	while (pos > 0 && buf[pos - 1] != ' ')
		--pos;
	if ((new = (char*)malloc(sizeof(*new) * ((old_pos - pos) + 1))) == NULL)
		return (NULL);
	i = 0;
	while (pos < old_pos && buf[pos] != ' ')
		new[i++] = buf[pos++];
	new[i] = '\0';
	return (new);
}

static void		delete_entry(char *ret)
{
	while (*ret)
	{
		if (*ret == '\n')
			*ret = ' ';
		++ret;
	}
}

static void		launch_callback(t_nboon *l, t_line *line, const char *word)
{
	size_t		len;
	char		*ret;
	t_uint		i;

	len = nb_strlen(word);
	nb_disable_raw(STDIN_FILENO);
	if ((ret = g_completion_callback(line, word, len)) != NULL)
	{
		i = 0;
		while (word[i] && ret[i] && word[i] == ret[i])
			++i;
		len = nb_strlen(ret + i);
		delete_entry(ret + i);
		if (ret[i] && l->b_len + len < LINE_BUF_SIZE)
			insert_utf8(l, &ret[i], len);
		else
			write(STDERR_FILENO, "\x7", 1);
		free(ret);
	}
	nb_enable_raw(STDIN_FILENO);
	g_refresh_fn(l);
}

void			tab_evt(t_nboon *l)
{
	t_line		line;
	char		*word;

	line.buf = l->buf;
	line.pos = l->b_pos;
	line.size = l->b_len;
	if (g_completion_callback != NULL)
	{
		word = get_prev_word(l->buf, l->b_pos);
		launch_callback(l, &line, word);
		free(word);
	}
}
