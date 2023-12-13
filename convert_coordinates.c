/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_coordinates.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:29 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/13 21:53:35 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_z_axis(t_info *fdf)
{
	int		point_index;
	double	tmp_x;
	double	tmp_y;
	double	angle;

	angle = -(M_PI_4);
	point_index = 0;
	while (point_index < fdf->points)
	{
		tmp_x = fdf->xyz[point_index].x;
		tmp_y = fdf->xyz[point_index].y;
		fdf->xyz[point_index].x = tmp_x * cos (angle) - tmp_y * sin (angle);
		fdf->xyz[point_index].y = tmp_x * sin (angle) + tmp_y * cos (angle);
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
		fdf->xyz[point_index].z = tmp_y * sin(angle) + tmp_z * cos(angle);
		point_index++;
	}
}


static void	get_inienlargevalue(t_info *fdf)
{
	get_min_coordinates(fdf);
	get_max_coordinates(fdf);
	fdf->enlarge_rate_x = (WIDTH / (fdf->max_x - fdf->min_x)) * 0.9;
	fdf->enlarge_rate_y = (HEIGHT / (fdf->max_y - fdf->min_y)) * 0.9;
}

void	get_inimovevalue(t_info *fdf)
{
	get_min_coordinates(fdf);
	get_max_coordinates(fdf);
	fdf->move_x = (WIDTH / 2) - ((fdf->max_x + fdf->min_x) / 2);
	fdf->move_y = (HEIGHT / 2) - ((fdf->max_y + fdf->min_y) / 2);
}

int	convert_coordinates(t_info *fdf)
{
	rotate_z_axis(fdf);
	rotate_x_axis(fdf);
	get_inienlargevalue(fdf);
	enlarge_frame(fdf, fdf->enlarge_rate_x, fdf->enlarge_rate_y);
	get_inimovevalue(fdf);
	move_frame(fdf, fdf->move_x, fdf->move_y);
	return (NO_ERROR);
}
