/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:23:14 by jzak              #+#    #+#             */
/*   Updated: 2014/03/01 18:37:51 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include "nboon.h"

static t_completion_fn		*completion_callback = NULL;

void			nb_set_completion_callback(t_completion_fn *fn)
{
	completion_callback = fn;
}

void			tab_evt(t_nboon *l)
{
	(void)l;
	if (completion_callback != NULL)
	{
		completion_callback(l->buf, LINE_BUF_SIZE);
		l->b_len = nb_strlen(l->buf);
		refresh_line(l);
	}
}
