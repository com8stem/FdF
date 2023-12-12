/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:02:11 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/12 15:26:12 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	checklen(char *filename)
{
	if (ft_strlen(filename) <= ft_strlen(".fdf"))
		ft_put_originalerror("filename is invalid!");
	return (NO_ERROR);
}

static int	checkdot(char *filename)
{
	int	dotcount;

	dotcount = 0;
	while (*filename != '\0')
	{
		if (*filename == '.')
			dotcount++;
		filename++;
	}
	if (dotcount > 1)
		ft_put_originalerror("extension is invalid!");
	return (NO_ERROR);
}

int	check_filename(char *filename)
{
	checklen(filename);
	checkdot(filename);
	while (*filename != '.')
		filename++;
	if (ft_strncmp(filename, ".fdf\0", ft_strlen(".fdf") + 1) != 0)
		ft_put_originalerror("extension is invalid!");
	return (0);
}
