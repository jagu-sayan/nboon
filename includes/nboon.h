/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nboon.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 00:48:09 by jzak              #+#    #+#             */
/*   Updated: 2014/03/01 18:40:57 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBOON_H
# define NBOON_H
# include <stdlib.h>

/*
** Public api of new boon library
** a realine alternative that use vt100
*/

/*
** Function pointer called when tab is pressed
*/
typedef void (t_completion_fn)(char *buf, size_t max_size);

/*
** mode.c
*/
int				nb_enable_raw(int fd);
void			nb_disable_raw(int fd);
void			nb_clear_screen(void);

/*
** nboon.c
*/
char			*nb_get_line(const char *prompt);

/*
** completion.c
*/
void			nb_set_completion_callback(t_completion_fn fn);

/*
** history.c
*/
int				nb_history_init(size_t max_size);
void			nb_history_next();
void			nb_history_prev();
int				nb_history_add(const char *line);
void			nb_history_free(void);

/*
** history_file.c
*/
int				nb_history_save(const char *filename);
int				nb_history_load(const char *filename);

#endif /* NBOON_H */
