/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:34:28 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 18:32:30 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

static struct termios	g_orig_termios;
static int				g_is_raw = 0;

/*
** Input modes: no break, no CR to NL, no parity check, no strip char,
** no start/stop output control.
** Output modes - disable post processing
** Control modes - set 8 bit chars
** Local modes - choing off, canonical off, no extended functions,
** no signal chars (^Z,^C)
** errno = ENOTTY;
*/
int				nb_enable_raw(int fd)
{
	struct termios		raw;

	if (tcgetattr(fd, &g_orig_termios) == -1)
		return (-1);

	raw = g_orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | IUTF8);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSAFLUSH, &raw) < 0)
		return (-1);
	g_is_raw = 1;
	return (0);
}

void			nb_clear_screen(void)
{
	write(STDIN_FILENO, "\x1b[H\x1b[2J", 7);
}

void			nb_disable_raw(int fd)
{
	if (g_is_raw && tcsetattr(fd, TCSAFLUSH, &g_orig_termios) != -1)
		g_is_raw = 0;
}
