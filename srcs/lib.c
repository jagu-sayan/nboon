/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 04:10:42 by jzak              #+#    #+#             */
/*   Updated: 2014/02/26 17:13:39 by jzak             ###   ########.fr       */
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
	size_t		size;
	char		*new;
	char		*save;

	size = nb_strlen(s1);
	new = (char*)malloc(sizeof(*new) * (size + 1));
	if (new == NULL)
		return (NULL);
	save = new;
	while (*s1 != '\0')
		*new++ = *s1++;
	*new = '\0';
	return (save);
}

void			*nb_memcpy(void *s1, const void *s2, size_t n)
{
	const char	*str2;
	char		*str1;
	size_t		i;

	i = 0;
	str1 = (char*)s1;
	str2 = (const char*)s2;
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (s1);
}

void			*nb_memmove(void *s1, const void *s2, size_t n)
{
	const char	*src;
	char		*dest;

	dest = (char*)s1;
	src = (const char*)s2;
	if (s1 == s2)
		return (s1);
	if (s2 > s1)
		return (nb_memcpy(dest, src, n));
	while (n > 0)
	{
		dest[n - 1] = src[n - 1];
		--n;
	}
	return (s1);
}
