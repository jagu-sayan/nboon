/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:24:09 by jzak              #+#    #+#             */
/*   Updated: 2014/03/26 15:24:10 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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

int				nb_atoi(const char *str)
{
	int		result;
	int		multiply;

	while ((*str > 8 && *str < 14) || (*str == ' '))
		str++;
	multiply = 1;
	if (*str == '-' || *str == '+')
		multiply = 44 - *str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	return (result * multiply);
}

char			*nb_itoa(int n)
{
	char	*new;
	size_t	size;
	int		tmp;

	tmp = n;
	size = 0;
	while (++size && tmp)
		tmp /= 10;
	if ((new = malloc(size + 1)) == NULL)
		return (NULL);
	if (n == 0)
		*new = '0';
	else if (n > 0 && (n = -n))
		--size;
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
