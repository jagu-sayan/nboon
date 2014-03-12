/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak </var/mail/jzak>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 17:23:03 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 19:46:20 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H
# include <stdlib.h>

# define LINE_BUF_SIZE  4096
# define WRITE_BUF_SIZE 32
# define HISTORY_SIZE   0

# define ESC       27
# define UP_KEY    65
# define DOWN_KEY  66
# define RIGHT_KEY 67
# define LEFT_KEY  68

# define DELETE    126
# define TAB       9
# define ENTER     13
# define CTRL_C    3
# define BACKSPACE 127
# define CTRL_H    8
# define CTRL_D    4
# define CTRL_T    20
# define CTRL_B    2
# define CTRL_F    6
# define CTRL_P    16
# define CTRL_N    14
# define CTRL_U    21
# define CTRL_K    11
# define CTRL_A    1
# define CTRL_E    5
# define CTRL_L    12
# define CTRL_W    23
# define CTRL_V    22

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
void			ctrl_t_evt(t_nboon *l);
void			ctrl_p_evt(t_nboon *l);
void			ctrl_n_evt(t_nboon *l);
void			ctrl_u_evt(t_nboon *l);
void			ctrl_k_evt(t_nboon *l);
void			ctrl_a_evt(t_nboon *l);
void			ctrl_e_evt(t_nboon *l);
void			ctrl_l_evt(t_nboon *l);
void			ctrl_w_evt(t_nboon *l);
void			move_right_evt(t_nboon *l);
void			move_left_evt(t_nboon *l);
void			delete_evt(t_nboon *l);

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
