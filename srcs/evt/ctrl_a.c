/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 05:09:14 by jzak              #+#    #+#             */
/*   Updated: 2014/02/27 19:08:53 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nboon.h"

void			ctrl_a_evt(t_nboon *l)
{
	l->b_pos = 0;
	refresh_line(l);
}