/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:34:28 by jzak              #+#    #+#             */
/*   Updated: 2014/02/26 13:20:52 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>

static struct termios	orig_termios;
static int				is_raw = 0;

//errno = ENOTTY;
int				enable_raw(int fd)
{
	struct termios		raw;

	if (tcgetattr(fd, &orig_termios) == -1)
		return (-1);

	raw = orig_termios; /* modify the original mode */
	/* input modes: no break, no CR to NL, no parity check, no strip char,
	 * * no start/stop output control. */
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	/* output modes - disable post processing */
	raw.c_oflag &= ~(OPOST);
	/* control modes - set 8 bit chars */
	raw.c_cflag |= (CS8);
	/* local modes - choing off, canonical off, no extended functions,
	 * * no signal chars (^Z,^C) */
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	/* control chars - set return condition: min number of bytes and timer.
	 * * We want read to return every single byte, without timeout. */
	raw.c_cc[VMIN] = 1; raw.c_cc[VTIME] = 0; /* 1 byte, no timer */
	/* put terminal in raw mode after flushing */
	if (tcsetattr(fd, TCSAFLUSH, &raw) < 0)
		return (-1);
	is_raw = 1;
	return (0);
}

void				disable_raw(int fd)
{
	if (is_raw && tcsetattr(fd, TCSAFLUSH, &orig_termios) != -1)
		is_raw = 0;
}
