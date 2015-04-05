/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:22:36 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:10:28 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic.h"

int					g_nb_error = -1;

static const char	*g_nb_str_error[] =
{
	TO_LONG(),
	NO_TERM()
};

const char		*nb_get_error(void)
{
	if (g_nb_error < 2)
		return (g_nb_str_error[g_nb_error]);
	else
		return ("");
}
