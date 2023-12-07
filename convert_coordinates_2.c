/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_coordinates_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:20:19 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/07 21:20:56 by kishizu          ###   ########.fr       */
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
