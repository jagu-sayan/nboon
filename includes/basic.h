/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:31:46 by jzak              #+#    #+#             */
/*   Updated: 2015/04/05 12:49:44 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_H
# define BASIC_H

# include <stdlib.h>

# define STR_HELPER(x) #x
# define STR(x) STR_HELPER(x)
# define LINE_BUF_SIZE  4096
# define WRITE_BUF_SIZE 32
# define HISTORY_SIZE   0

/*
** Basic type
*/
# ifndef UINT
#  define UINT

typedef unsigned int	t_uint;
# endif

# ifndef UTF8
#  define UTF8

typedef unsigned int	t_utf8;
# endif

# ifndef T_SIZE
#  define T_SIZE

typedef struct winsize	t_size;
# endif

/*
** Message error
*/
typedef enum			e_nb_error
{
	ERR_TO_LONG = 0,
	ERR_NO_TERM = 1,
}						t_nb_error;

# define TO_LONG() "The string is to long ("STR(LINE_BUF_SIZE)" characters max)"
# define NO_TERM() "The standard input is not a terminal."

/*
** The s_nboon structure represents the state during line editing.
** We pass this state to functions implementing specific editing
** functionalities.
*/
typedef struct			s_nboon
{
	int					fd;
	char				*paste_line;
	char				*save_line;
	char				buf[LINE_BUF_SIZE];
	t_uint				b_len;
	t_uint				b_pos;
	t_uint				b_curor;
	t_uint				b_curor_end;
	char				*prompt;
	t_uint				p_len;
	t_uint				p_cursor;
	t_uint				nbr_rows;
}						t_nboon;

/*
** Callback that refresh struct s_nboon
*/
typedef void			(*t_refresh_fn)(t_nboon *line);

/*
** Global (history.c, completiom.c)
*/
extern char				**g_history;
extern size_t			g_history_size;
extern t_uint			g_history_idx;
extern t_uint			g_history_pos;
extern t_refresh_fn		g_refresh_fn;
extern int				g_nb_error;

#endif
