/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nboon.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 00:48:09 by jzak              #+#    #+#             */
/*   Updated: 2014/02/28 16:13:49 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBOON_H
# define NBOON_H
# include <stdlib.h>

# define LINE_BUF_SIZE  4096
# define WRITE_BUF_SIZE 32
# define HISTORY_SIZE   4096

# define ESC       0x1b

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
# define ESCAPE    27

typedef unsigned int	t_uint;

/*
** The s_nboon structure represents the state during line editing.
** We pass this state to functions implementing specific editing
** functionalities.
*/
typedef struct			s_nboon
{
	int					fd;
	char				*buf;
	t_uint				b_len;
	t_uint				b_pos;
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
** Private function (refresh.c)
*/
void			refresh_line(t_nboon *l);

/*
** Event function (in evt folder)
*/
void			tab_evt(t_nboon *l);
void			enter_evt(t_nboon *l);
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

/*
** Escape event function (evt/escape.c)
*/
void			escape_evt(t_nboon *l);
void			move_right_evt(t_nboon *l);
void			move_left_evt(t_nboon *l);
void			delete_evt(t_nboon *l);

/*
** Public api (mode.c, nboon.c, history.c)
*/
int				nb_enable_raw(int fd);
void			nb_disable_raw(int fd);
char			*nb_get_line(const char *prompt);
int				nb_history_set_max_size(size_t size);
int				nb_history_add(const char *line);
int				nb_history_save(const char *filename);
int				nb_history_load(const char *filename);

#endif /* NBOON_H */
