/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_coordinates_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:20:19 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/15 17:38:55 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_min_coordinates(t_info *fdf)
{
	int		point_index;
	double	tmp_x;
	double	min_x;
	double	tmp_y;
	double	min_y;

	point_index = 0;
	while (point_index < fdf->points)
	{
		tmp_x = fdf->xyz[point_index].x;
		tmp_y = fdf->xyz[point_index].y;
		if (point_index != 0 && tmp_x < min_x)
			min_x = tmp_x;
		if (point_index != 0 && tmp_y < min_y)
			min_y = tmp_y;
		if (point_index == 0)
		{
			min_x = tmp_x;
			min_y = tmp_y;
		}
		point_index++;
	}
	fdf->min_x = min_x;
	fdf->min_y = min_y;
}

void	get_max_coordinates(t_info *fdf)
{
	int		point_index;
	double	tmp_x;
	double	max_x;
	double	tmp_y;
	double	max_y;

	point_index = 0;
	while (point_index < fdf->points)
	{
		tmp_x = fdf->xyz[point_index].x;
		tmp_y = fdf->xyz[point_index].y;
		if (point_index != 0 && tmp_x > max_x)
			max_x = tmp_x;
		if (point_index != 0 && tmp_y > max_y)
			max_y = tmp_y;
		if (point_index == 0)
		{
			max_x = tmp_x;
			max_y = tmp_y;
		}
		point_index++;
	}
	fdf->max_x = max_x;
	fdf->max_y = max_y;
}

void	get_max_min_z_coordinates(t_info *fdf)
{
	int		point_index;
	double	tmp_z;
	double	max_z;
	double	min_z;

	point_index = 0;
	while (point_index < fdf->points)
	{
		tmp_z = fdf->xyz[point_index].z;
		if (point_index != 0 && tmp_z > max_z)
			max_z = tmp_z;
		if (point_index != 0 && tmp_z < min_z)
			min_z = tmp_z;
		if (point_index == 0)
		{
			max_z = tmp_z;
			min_z = tmp_z;
		}
		point_index++;
	}
	fdf->max_z = max_z;
	fdf->min_z = min_z;
}

void	move_frame(t_info *fdf, double move_x, double move_y)
{
	int		point_index;

	point_index = 0;
	while (point_index < fdf->points)
	{
		fdf->xyz[point_index].x = fdf->xyz[point_index].x + move_x;
		fdf->xyz[point_index].y = fdf->xyz[point_index].y + move_y;
		point_index++;
	}
}

void	enlarge_frame(t_info *fdf, double enlarge_rate_x, double enlarge_rate_y)
{
	int		point_index;
	double	rate;

	point_index = 0;
	if (enlarge_rate_x < enlarge_rate_y)
		rate = enlarge_rate_x;
	else
		rate = enlarge_rate_y;
	while (point_index < fdf->points)
	{
		fdf->xyz[point_index].x = fdf->xyz[point_index].x * rate;
		fdf->xyz[point_index].y = fdf->xyz[point_index].y * rate;
		point_index++;
	}
}
