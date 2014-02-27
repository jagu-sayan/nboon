/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak </var/mail/jzak>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 14:04:54 by jzak              #+#    #+#             */
/*   Updated: 2014/02/27 14:54:19 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> // XXX
#include "nboon.h"

void			refresh_line(t_nboon *l)
{
	write(l->fd, "\x1b[s", nb_strlen("\x1b[s"));
	/* write(l->fd, "\x1b[0G\x1b[0K", nb_strlen("\x1b[0G\x1b[0K")); */

	write(l->fd, "\x1b[0G", nb_strlen("\x1b[0G"));
	write(l->fd, l->prompt, l->plen),
	write(l->fd, l->buf, l->len);
	/* write(l->fd, "\x1b[0G", nb_strlen("\x1b[0G")); */
	write(l->fd, "\x1b[u", nb_strlen("\x1b[u"));
	write(l->fd, "\x1b[1C", nb_strlen("\x1b[1C"));

}

