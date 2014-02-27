/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nboon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 00:53:03 by jzak              #+#    #+#             */
/*   Updated: 2014/02/27 20:01:20 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>
#include "nboon.h"

//errno = ENOTTY;
static int		execute_evt(t_nboon *s, int evt)
{
	int			i;
	t_nbevent	evt_fn[]= {
		{ TAB, tab_evt },
		{ ENTER, enter_evt },
		{ BACKSPACE, backspace_evt },
		{ CTRL_H, backspace_evt },
		{ CTRL_T, ctrl_t_evt },
		{ CTRL_B, move_left_evt },
		{ CTRL_F, move_right_evt },
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

static void		insert_char(t_nboon *l, char c)
{
	if (l->b_len < LINE_BUF_SIZE)
	{
		if (l->b_len != l->b_pos)
			nb_memmove(&l->buf[l->b_pos + 1], &l->buf[l->b_pos], l->b_len - l->b_pos);
		l->buf[l->b_pos] = c;
		l->b_pos++;
		l->b_len++;
		l->buf[l->b_len] = '\0';
		refresh_line(l);
	}
}

static int		get_columns(void)
{
	struct winsize		ws;

	if (ioctl(1, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (80);
	return (ws.ws_col);
}

static int		line_edit(int fd, char *buf, const char *prompt)
{
	t_nboon		line;
	char		c;

	line.fd = fd;
	line.buf = buf;
	line.b_len = 0;
	line.b_pos = 0;
	line.prompt = prompt;
	line.p_len = nb_strlen(prompt);
	line.cols = get_columns();
	line.rows = 0;
	buf[0] = '\0';
	write(fd, prompt, line.p_len);
	while (read(fd, &c, 1) > 0)
	{
		if (c == CTRL_D)
		{
			if (line.b_len == 0)
				return (-1);
			delete_evt(&line);
		}
		else if (c == CTRL_C || c == ENTER)
			return (0);
		else if (c == CTRL_V)
			return (0);
		else if (execute_evt(&line, c) == 0)
			insert_char(&line, c);
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
	char	buf[LINE_BUF_SIZE];
	int		count;

	count = -1;
	if (isatty(STDIN_FILENO) && nb_enable_raw(STDIN_FILENO) != -1)
	{
		count = line_edit(STDIN_FILENO, buf, prompt);
		nb_disable_raw(STDIN_FILENO);
		write(1, "\n", 1);
		if (count == -1)
			return (NULL);
	}
	else
		return (NULL);
	return (nb_strdup(buf));
}
