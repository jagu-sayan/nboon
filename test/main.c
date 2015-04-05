/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 21:36:31 by jzak              #+#    #+#             */
/*   Updated: 2014/03/27 21:36:46 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nboon.h"

int		main(void)
{
	char	*line;
	int		ret;

	nb_history_init(4);
	nb_history_load("history.txt");
	while ((ret = nb_get_line("hello> ", &line)) != NB_EXIT)
	{
		if (ret == NB_ERROR)
			dprintf(2, "%s\n", nb_get_error());
		else if (ret != NB_INTERRUPT && line[0] != '\0' && line[0] != '/')
		{
			printf("echo: '%s'\n", line);
			nb_history_add(line);
		}
		free(line);
	}
	nb_history_save("history.txt");
	nb_history_free();
	return (0);
}
