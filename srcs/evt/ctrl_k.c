/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_k.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:13 by jzak              #+#    #+#             */
/*   Updated: 2014/02/27 19:05:36 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nboon.h"

void			ctrl_k_evt(t_nboon *l)
{
	l->buf[l->b_pos] = '\0';
	l->b_len = l->b_pos;
	refresh_line(l);
}
