/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 04:03:09 by jzak              #+#    #+#             */
/*   Updated: 2014/02/27 19:45:09 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nboon.h"

int		main(void)
{
	char	*line;
	
	//nb_set_completion_callback(completion);
	//nb_history_load("history.txt");
	//nb_history_set_max_len(len);
	while((line = nb_get_line("hello> ")) != NULL)
	{
		/* Do something with the string. */
		if (line[0] != '\0' && line[0] != '/')
		{
			printf("echo: '%s'\n", line);
			//nb_history_add(line);
			//nb_history_save("history.txt");
			//parse_shell();
		}
		free(line);
	}
	return (0);
}
