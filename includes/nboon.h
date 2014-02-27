/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nboon.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 00:48:09 by jzak              #+#    #+#             */
/*   Updated: 2014/02/27 14:09:00 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBOON_H
# define NBOON_H
# include <stdlib.h>

# define MAX_LINE 4096

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
# define ESCAPE    27

/*
** The s_nboon structure represents the state during line editing.
** We pass this state to functions implementing specific editing
** functionalities.
*/
typedef struct		s_nboon
{
	int				fd;
	char			*buf;
	size_t			buflen;
	const char *	prompt;
	size_t			plen;
	size_t			pos;
	size_t			oldpos;
	size_t			len;
	size_t			cols;
	size_t			maxrows;
	int				history_index;
}					t_nboon;

typedef struct		s_nbevent
{
	int				evt;
	void(*fn)(t_nboon*);
}					t_nbevent;

/*
** Utility function (lib.c)
*/
size_t			nb_strlen(const char *str);
char			*nb_strdup(const char *s1);
void			*nb_memcpy(void *s1, const void *s2, size_t n);
void			*nb_memmove(void *s1, const void *s2, size_t n);

int				enable_raw(int fd);
void			disable_raw(int fd);

void			refresh_line(t_nboon *l);

/*
** Event function (in evt folder)
*/
void			tab_evt(t_nboon *s);
void			enter_evt(t_nboon *s);
void			backspace_evt(t_nboon *s);
void			ctrl_h_evt(t_nboon *s);
void			ctrl_t_evt(t_nboon *s);
void			ctrl_b_evt(t_nboon *s);
void			ctrl_f_evt(t_nboon *s);
void			ctrl_p_evt(t_nboon *s);
void			ctrl_n_evt(t_nboon *s);
void			ctrl_u_evt(t_nboon *s);
void			ctrl_k_evt(t_nboon *s);
void			ctrl_a_evt(t_nboon *s);
void			ctrl_e_evt(t_nboon *s);
void			ctrl_l_evt(t_nboon *s);
void			ctrl_w_evt(t_nboon *s);
void			escape_evt(t_nboon *s);

/*
** Public api (nboon.c)
*/
char			*get_line(const char *prompt);

#endif /* NBOON_H */
