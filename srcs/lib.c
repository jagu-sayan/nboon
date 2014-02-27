/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 04:10:42 by jzak              #+#    #+#             */
/*   Updated: 2014/02/27 18:00:00 by jzak             ###   ########.fr       */
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

void			*nb_memmove(void *s1, const void *s2, size_t n)
{
	const char	*src;
	char		*dest;

	dest = (char*)s1;
	src = (const char*)s2;
	if (s2 > s1)
	{
		while (n--)
			*dest++ = *src++;
	}
	else if (s1 != s2)
	{
		while (n--)
			dest[n] = src[n];
	}
	return (s1);
}

static size_t	nbr_digit(int n)
{
	int		size;

	size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char			*nb_itoa(int n)
{
	char	*new;
	size_t	size;

	size = nbr_digit(n);
	if ((new = malloc(size + 1)) == NULL)
		return (NULL);
	if (n == 0)
		*new = '0';
	else if (n > 0)
	{
		n = -n;
		--size;
	}
	else
		*new = '-';
	new[size] = '\0';
	while (n != 0)
	{
		new[--size] = n % -10 * -1 + '0';
		n /= -10 * -1;
	}
	return (new);
}
