/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_coordinates_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:38:48 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/15 17:39:15 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_draw(t_info *fdf)
{
	int	point_index;

	point_index = 0;
	while (point_index < fdf->points)
	{
		fdf->xyz[point_index].x = fdf->xyz[point_index].ini_x;
		fdf->xyz[point_index].y = fdf->xyz[point_index].ini_y;
		fdf->xyz[point_index].z = fdf->xyz[point_index].ini_z;
		point_index++;
	}
	convert_coordinates(fdf);
}
