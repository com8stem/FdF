/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:12:23 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/01 20:26:56 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_map(char *argv)
{
	char	*line;
	
	int		fd;
	int		count;

	fd = open (argv, O_RDONLY);
	if (fd == -1)
		error_out("open");
	count = 0;
	while (count++ == 0 || line != NULL)
	{
		line = get_next_line(fd);
		
	}
}
