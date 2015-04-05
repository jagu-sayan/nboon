/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:24:49 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 18:16:31 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t			nb_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}

char			*nb_strdup(const char *s1)
{
	char		*new;
	char		*save;

	new = (char*)malloc(sizeof(*new) * (nb_strlen(s1) + 1));
	if (new == NULL)
		return (NULL);
	save = new;
	while (*s1 != '\0')
		*new++ = *s1++;
	*new = '\0';
	return (save);
}

int				nb_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((int)(*s1 - *s2));
}

char			*nb_strncpy(char *s1, const char *s2, size_t n)
{
	char	*dst_ptr;

	dst_ptr = s1;
	while (n-- > 0)
	{
		*s1++ = *s2;
		if (*s2 != '\0')
			s2++;
	}
	return (dst_ptr);
}
