/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 16:28:27 by jzak              #+#    #+#             */
/*   Updated: 2014/03/14 19:36:36 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H
# include <stdlib.h>

# define LINE_BUF_SIZE  4096
# define WRITE_BUF_SIZE 32
# define HISTORY_SIZE   0

typedef enum			e_key_evt
{
	CTRL_A = 1,
	CTRL_B = 2,
	CTRL_C = 3,
	CTRL_D = 4,
	CTRL_E = 5,
	CTRL_F = 6,
	CTRL_G = 7,
	CTRL_H = 8,
	HT_TAB = 9,
	CTRL_I = 9,
	CTRL_J = 10,
	CTRL_K = 11,
	CTRL_L = 12,
	CTRL_M = 13,
	ENTER  = 13,
	CTRL_N = 14,
	CTRL_O = 15,
	CTRL_P = 16,
	CTRL_Q = 17,
	CTRL_R = 18,
	CTRL_S = 19,
	CTRL_T = 20,
	CTRL_U = 21,
	CTRL_V = 22,
	CTRL_W = 23,
	CTRL_X = 24,
	CTRL_Y = 25,
	CTRL_Z = 26,
	ESCAPE = 27,
	BACKSPACE = 127
}						t_key_evt;

typedef enum			e_escape_evt
{
	SHIFT_KEY  = '2',
	CTRL_KEY   = '5',
	UP_KEY     = 'A',
	DOWN_KEY   = 'B',
	RIGHT_KEY  = 'C',
	LEFT_KEY   = 'D',
	HOME_KEY   = 'H',
	END_KEY    = 'F',
	DELETE_KEY = '~'
}						t_escpae_evt;

/*
** Basic type
*/
typedef unsigned int	t_uint;
typedef unsigned int	t_utf8;

/*
** Global (history.c)
*/
extern char				**g_history;
extern size_t			g_history_size;
extern t_uint			g_history_idx;

/*
** Interval structure for binary search
*/
typedef struct			s_interval
{
	t_utf8				first;
	t_utf8				last;
}						t_interval;

/*
** The s_nboon structure represents the state during line editing.
** We pass this state to functions implementing specific editing
** functionalities.
*/
typedef struct			s_nboon
{
	int					fd;
	char				buf[LINE_BUF_SIZE];
	t_uint				b_len;
	t_uint				b_pos;
	t_uint				b_curor;
	const char *		prompt;
	t_uint				p_len;
	t_uint				cols;
	t_uint				rows;
	t_uint				history_index;
}						t_nboon;

typedef void(*t_nbevent_fn)(t_nboon*);

typedef struct			s_nbevent
{
	int					evt;
	t_nbevent_fn		fn;
}						t_nbevent;

/*
** Utility function (lib.c)
*/
size_t			nb_strlen(const char *str);
char			*nb_strdup(const char *s1);
void			*nb_memmove(void *s1, const void *s2, size_t n);
char			*nb_itoa(int n);

/*
** Core function (refresh.c)
*/
void			refresh_line(t_nboon *l);

/*
** Event function (in evt folder and evt.c)
*/
int				execute_evt(t_nboon *l, int evt, char *key);
void			backspace_evt(t_nboon *l);
void			delete_evt(t_nboon *l);
void			move_right_evt(t_nboon *l);
void			move_left_evt(t_nboon *l);
void			move_home_evt(t_nboon *l);
void			move_end_evt(t_nboon *l);
void			move_to_next_word_evt(t_nboon *l);
void			move_to_prev_word_evt(t_nboon *l);
void			clear_screen_evt(t_nboon *l);
void			clear_line_evt(t_nboon *l);
void			clear_end_line_evt(t_nboon *l);
void			history_prev_evt(t_nboon *l);
void			history_next_evt(t_nboon *l);
void			del_word_evt(t_nboon *l);
void			swap_letter_evt(t_nboon *l);

/*
** Tab completion evt (completion.c)
*/
void			tab_evt(t_nboon *l);

/*
** unicode.c
*/
int				get_display_width(t_utf8 c);
t_utf8			get_next_char(const char *s, t_uint *idx);
t_utf8			get_prev_char(const char *s, t_uint *idx);

#endif /* INTERNAL_H */
