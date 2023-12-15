/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:02:11 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/15 19:14:47 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	checklen(char *filename)
{
	if (ft_strlen(filename) <= ft_strlen(".fdf"))
		ft_put_originalerror("filename is invalid!");
	return (NO_ERROR);
}

int	check_filename(char *filename)
{
	checklen(filename);
	while (*filename != '\0')
		filename++;
	filename = filename - ft_strlen(".fdf");
	if (ft_strncmp(filename, ".fdf\0", ft_strlen(".fdf") + 1) != 0)
		ft_put_originalerror("extension is invalid!");
	return (NO_ERROR);
}
