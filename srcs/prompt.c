/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:24:37 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 15:24:58 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "internal.h"

t_uint			expand_prompt(const char *prompt, char **ret)
{
	t_uint		size;
	t_uint		i;
	char		*new;

	i = 0;
	size = nb_strlen(prompt);
	if ((new = (char*)malloc(sizeof(*new) * (size + 1))) == NULL)
		return (0);
	while (*prompt)
	{
		if (*prompt != 1 && *prompt != 2)
			new[i++] = *prompt;
		++prompt;
	}
	new[i] = '\0';
	*ret = new;
	return (i);
}
