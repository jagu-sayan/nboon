/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 04:03:09 by jzak              #+#    #+#             */
/*   Updated: 2014/03/14 19:09:48 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nboon.h"

#define HISTORY_FILE "history.txt"
int		main(void)
{
	char	*line;
	
	//nb_set_completion_callback(completion);
	nb_history_init(4);
	nb_history_load(HISTORY_FILE);
	while((line = nb_get_line("hello> ")) != NULL)
	{
		/* Do something with the string. */
		if (line[0] != '\0' && line[0] != '/')
		{
			printf("echo: '%s'\n", line);
			nb_history_add(line);
			//parse_shell();
		}
		free(line);
	}
	nb_history_save(HISTORY_FILE);
	nb_history_free();
	return (0);
}
