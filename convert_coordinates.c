/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_coordinates.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:29 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/05 21:17:10 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_z_axis(t_info *fdf)
{
	int		point_index;
	double	tmp_x;
	double	tmp_y;
	double	angle;

	angle = M_PI_4;
	point_index = 0;
	while (point_index < fdf->points)
	{
		tmp_x = fdf->xyz[point_index].x;
		tmp_y = fdf->xyz[point_index].y;
		fdf->xyz[point_index].x = tmp_x * cos (angle) - tmp_y * sin (angle);
		fdf->xyz[point_index].x = tmp_x * sin (angle) + tmp_y * cos (angle);
		point_index++;
	}
}

static void	rotate_x_axis(t_info *fdf)
{
	int		point_index;
	double	tmp_y;
	double	tmp_z;
	double	angle;

	angle = atan(sqrt(2));
	point_index = 0;
	while (point_index < fdf->points)
	{
		tmp_y = fdf->xyz[point_index].y;
		tmp_z = fdf->xyz[point_index].z;
		fdf->xyz[point_index].y = tmp_y * cos(angle) - tmp_z * sin(angle);
		fdf->xyz[point_index].z = tmp_y * sin(angle) - tmp_z * cos(angle);
		point_index++;
	}
}

int	convert_coordinates(t_info *fdf)
{
	rotate_z_axis(fdf);
	rotate_x_axis(fdf);
	return (NO_ERROR);
}
