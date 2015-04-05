/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nboon.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:35:12 by jzak              #+#    #+#             */
/*   Updated: 2014/03/27 21:36:00 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBOON_H
# define NBOON_H

# include <stdlib.h>
# include "basic.h"

/*
** Public api of new boon library
** a realine alternative that use vt100
*/

/*
** Function pointer called when tab is pressed
*/
typedef struct	s_line
{
	const char	*buf;
	t_uint		pos;
	t_uint		size;
}				t_line;

typedef char	*(t_comp_fn)(const t_line *line, const char *word, size_t n);

/*
** Status returned by nb_get_line
*/
typedef enum	e_nb_status
{
	NB_ERROR = -1,
	NB_SUCCESS = 0,
	NB_EXIT = 1,
	NB_INTERRUPT = 2
}				t_nb_status;

/*
** mode.c
*/
int				nb_enable_raw(int fd);
void			nb_disable_raw(int fd);
void			nb_clear_screen(void);

/*
** Core function (nboon.c, refresh.c, error.c)
*/
void			nb_refresh_size(int sig);
void			nb_set_refresh_callback(t_refresh_fn fn);
const char		*nb_get_error(void);

t_nb_status		nb_get_line(const char *prompt, char **line);
int				nb_ask_question(const char *question);

void			nb_refresh_multi_line(t_nboon *l);
void			nb_refresh_single_line(t_nboon *l);

/*
** completion.c
*/
void			nb_set_completion_callback(t_comp_fn fn);

/*
** history.c
*/
int				nb_history_init(size_t max_size);
int				nb_history_next();
int				nb_history_prev();
int				nb_history_add(const char *line);
void			nb_history_free(void);

/*
** history_file.c
*/
int				nb_history_save(const char *filename);
int				nb_history_load(const char *filename);

#endif
