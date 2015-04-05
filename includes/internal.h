/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:34:19 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:37:49 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H
# include <sys/ioctl.h>
# include "basic.h"

typedef enum		e_key_evt
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
	ENTER = 13,
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
}					t_key_evt;

typedef enum		e_escape_evt
{
	SHIFT_KEY = '2',
	CTRL_KEY = '5',
	UP_KEY = 'A',
	DOWN_KEY = 'B',
	RIGHT_KEY = 'C',
	LEFT_KEY = 'D',
	HOME_KEY = 'H',
	END_KEY = 'F',
	DELETE_KEY = '~'
}					t_escpae_evt;

typedef enum		e_nb_history
{
	NB_HISTORY_NEXT = 1,
	NB_HISTORY_PREV = 2
}					t_nb_history;

/*
** Function callback
*/
typedef void(*t_nbevent_fn)(t_nboon*);

typedef struct		s_nbevent
{
	int				evt;
	t_nbevent_fn	fn;
}					t_nbevent;

/*
** Interval structure for binary search
*/
typedef struct		s_interval
{
	t_utf8			first;
	t_utf8			last;
}					t_interval;

/*
** Utility function (string.c lib.c)
*/
size_t				nb_strlen(const char *str);
char				*nb_strncpy(char *s1, const char *s2, size_t n);
char				*nb_strdup(const char *s1);
int					nb_strcmp(const char *s1, const char *s2);
void				*nb_memmove(void *s1, const void *s2, size_t n);
int					nb_atoi(const char *str);
char				*nb_itoa(int n);

/*
** insert data in nboon buffer (insert.c)
*/
void				insert_utf8(t_nboon *l, char *data, int size);

/*
** Event function (in evt folder and evt.c)
*/
int					execute_evt(t_nboon *l, int evt, char *key);
void				backspace_evt(t_nboon *l);
void				delete_evt(t_nboon *l);
void				move_right_evt(t_nboon *l);
void				move_left_evt(t_nboon *l);
void				move_home_evt(t_nboon *l);
void				move_end_evt(t_nboon *l);
void				move_to_next_word_evt(t_nboon *l);
void				move_to_prev_word_evt(t_nboon *l);
void				clear_screen_evt(t_nboon *l);
void				clear_line_evt(t_nboon *l);
void				clear_end_line_evt(t_nboon *l);
void				history_next_evt(t_nboon *l, int cmd);
void				del_word_evt(t_nboon *l);
void				del_path_evt(t_nboon *l);
void				swap_letter_evt(t_nboon *l);
void				paste_line_evt(t_nboon *l);

/*
** Tab completion evt (completion.c)
*/
void				tab_evt(t_nboon *l);

/*
** unicode.c (utf8)
*/
int					get_display_width(t_utf8 c);
size_t				get_str_display_width(const char *str);

/*
** return 0 if the end or begin of the string is reached.
*/
t_utf8				get_next_char(const char *s, t_uint *idx);
t_utf8				get_prev_char(const char *s, t_uint *idx);

/*
** prompt.c
*/
t_uint				expand_prompt(const char *prompt, char **ret);

#endif
