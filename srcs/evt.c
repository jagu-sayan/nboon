/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 18:49:10 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 19:30:32 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static t_nbevent	g_evt_fn[]= {
		{ TAB, tab_evt },
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
		{ -1, NULL }
};

static void		escape_extended(t_nboon *l, char evt, char *key)
{
	if (evt == 51 && key[0] == DELETE)
		delete_evt(l);
}

static int		escape_evt(t_nboon *l, char *key)
{
	if (key[0] == '[')
	{
		if (key[1] == LEFT_KEY)
			move_left_evt(l);
		else if (key[1] == RIGHT_KEY)
			move_right_evt(l);
		else if (key[1] == UP_KEY)
			ctrl_p_evt(l);
		else if (key[1] == DOWN_KEY)
			ctrl_n_evt(l);
		else if (key[1] > 48 && key[1] < 55)
			escape_extended(l, key[1], &key[2]);
	}
	return (1);
}
/*
 ** errno = ENOTTY;
 */
int				execute_evt(t_nboon *l, int evt, char *key)
{
	int					i;

	i = 0;
	if (evt == ESC)
		return (escape_evt(l, key));
	while (g_evt_fn[i].evt != -1)
	{
		if (g_evt_fn[i].evt == evt)
		{
			g_evt_fn[i].fn(l);
			return (1);
		}
		++i;
	}
	return (0);
}

