/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mapinfo_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:31:50 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/12 16:32:57 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_xyz_color(t_info *fdf, int points, int x, int y)
{
	fdf->xyz[points].x = (double)x;
	fdf->xyz[points].y = (double)y;
	fdf->xyz[points].z = (double)fdf->map_int[y][x];
	fdf->xyz[points].ini_z = (double)fdf->map_int[y][x];
	fdf->xyz[points].color = (double)fdf->color[points];
}

void	set_coordinates(t_info *fdf)
{
	int	x;
	int	y;
	int	points;

	points = 0;
	y = 0;
	fdf->xyz = (t_coordinates *)malloc(((fdf->x_len) * (fdf->y_len))
			* sizeof(t_coordinates));
	if (fdf->xyz == NULL)
		ft_put_originalerror("failed to allocate!");
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			set_xyz_color(fdf, points, x, y);
			x++;
			points++;
		}
		y++;
	}
	free_mapint(fdf, fdf->map_int);
	fdf->points = points;
}
