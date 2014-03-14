/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 18:49:10 by jzak              #+#    #+#             */
/*   Updated: 2014/03/14 19:36:58 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static t_nbevent	g_evt_fn[]= {
		{ BACKSPACE, backspace_evt },
		{ CTRL_H, backspace_evt },
		{ CTRL_B, move_left_evt },
		{ CTRL_F, move_right_evt },
		{ CTRL_A, move_home_evt },
		{ CTRL_E, move_end_evt },
		{ CTRL_L, clear_screen_evt },
		{ CTRL_U, clear_line_evt },
		{ CTRL_K, clear_end_line_evt },
		{ CTRL_P, history_prev_evt },
		{ CTRL_N, history_next_evt },
		{ CTRL_W, del_word_evt },
		{ CTRL_T, swap_letter_evt },
		{ HT_TAB, tab_evt },
		{ -1, NULL }
};

static void		escape_extended(t_nboon *l, char evt, char *key)
{
	if (evt == '3' && key[0] == DELETE_KEY)
		delete_evt(l);
	else if (evt == '1' && key[0] == ';')
	{
		if (key[1] == SHIFT_KEY || key[1] == CTRL_KEY)
		{
			if (key[2] == LEFT_KEY)
				move_to_prev_word_evt(l);
			else if (key[2] == RIGHT_KEY)
				move_to_next_word_evt(l);
		}
	}
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
			history_prev_evt(l);
		else if (key[1] == DOWN_KEY)
			history_next_evt(l);
		else if (key[1] == HOME_KEY)
			move_home_evt(l);
		else if (key[1] == END_KEY)
			move_end_evt(l);
		else if (key[1] >= '0' && key[1] <= '9')
			escape_extended(l, key[1], &key[2]);
	}
	else if (key[0] == 'O')
	{
		if (key[1] == HOME_KEY)
			move_home_evt(l);
		else if (key[1] == END_KEY)
			move_end_evt(l);
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
	if (evt == ESCAPE)
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
	if (evt <= ESCAPE)
		return (1);
	return (0);
}
