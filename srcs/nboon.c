/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nboon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 00:53:03 by jzak              #+#    #+#             */
/*   Updated: 2014/02/26 18:18:23 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
//#include "libft.h"
#include "nboon.h"


//errno = ENOTTY;

static int		execute_evt(t_nboon *s, int evt)
{
	int			i;
	t_nbevent	evt_fn[]= {
		{ TAB, tab_evt },
		{ ENTER, enter_evt },
		{ BACKSPACE, backspace_evt },
		{ CTRL_H, ctrl_h_evt },
		{ CTRL_T, ctrl_t_evt },
		{ CTRL_B, ctrl_b_evt },
		{ CTRL_F, ctrl_f_evt },
		{ CTRL_P, ctrl_p_evt },
		{ CTRL_N, ctrl_n_evt },
		{ CTRL_U, ctrl_u_evt },
		{ CTRL_K, ctrl_k_evt },
		{ CTRL_A, ctrl_a_evt },
		{ CTRL_E, ctrl_e_evt },
		{ CTRL_L, ctrl_l_evt },
		{ CTRL_W, ctrl_w_evt },
		{ ESCAPE, escape_evt },
		{ -1, NULL }
	};

	i = 0;
	while (evt_fn[i].evt != -1)
	{
		if (evt_fn[i].evt == evt)
		{
			evt_fn[i].fn(s);
			return (1);
		}
		++i;
	}
	return (0);
}

#include <stdio.h>
void			refresh_line(t_nboon *l)
{
	write(l->fd, "\x1b[0G\x1b[0K", nb_strlen("\x1b[0G\x1b[0K"));

	write(l->fd, l->prompt, l->plen),
	write(l->fd, l->buf, l->len);
}

static void		insert_char(t_nboon *l, char c)
{
	if (l->len < l->buflen)
	{
		if (l->len != l->pos)
			nb_memmove(&l->buf[l->pos + 1], &l->buf[l->pos], l->len - l->pos);
		l->buf[l->pos] = c;
		l->pos++;
		l->len++;
		l->buf[l->len] = '\0';
		refresh_line(l);
	}
}

static int		line_edit(int fd, char *buf, size_t len, const char *prompt)
{
	t_nboon		state;
	char		c;

	state.fd = fd;
	state.buf = buf;
	state.buflen = len;
	state.prompt = prompt;
	state.plen = nb_strlen(prompt);
	state.oldpos = state.pos = 0;
	state.len = 0;
	buf[0] = '\0';
	write(fd, prompt, state.plen);
	while (read(fd, &c, 1) > 0)
	{
		if (c == CTRL_D)
			return (-1);
		else if (c == CTRL_C)
			return (0);
		execute_evt(&state, c);
		insert_char(&state, c);
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
char			*get_line(const char *prompt)
{
	char	buf[MAX_LINE];
	int		count;

	count = -1;
	if (isatty(STDIN_FILENO) && enable_raw(STDIN_FILENO) != -1)
	{
		count = line_edit(STDIN_FILENO, buf, MAX_LINE, prompt);
		disable_raw(STDIN_FILENO);
		write(1, "\n", 1);
		if (count == -1)
			return (NULL);
	}
	else
		return (NULL);
	return (nb_strdup(buf));
}
