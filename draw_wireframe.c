/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/12 20:42:45 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(x >= WIDTH || y >= HEIGHT) || (x < 0 || y < 0))
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static void	set_draw(t_info *fdf, int start_index, int end_index, t_data *img)
{
	t_lineinfo	tmp;

	tmp.start_x = fdf->xyz[start_index].x;
	tmp.start_y = fdf->xyz[start_index].y;
	tmp.start_color = 0xFFFFFF;
	tmp.end_x = fdf->xyz[end_index].x;
	tmp.end_y = fdf->xyz[end_index].y;
	tmp.end_color = 0xFFFFFF;
	if (fdf->color_flag == 1)
	{
		tmp.start_color = fdf->xyz[start_index].color;
		tmp.end_color = fdf->xyz[end_index].color;
	}
	tmp.start_z = fdf->xyz[start_index].ini_z;
	tmp.end_z = fdf->xyz[end_index].ini_z;
	drawline(tmp, img);
}

int	draw_wireframe(t_info *fdf, t_data *img)
{
	int			index;

	index = 0;
	while (index < fdf->points)
	{
		if ((index + 1) % fdf->x_len != 0)
			set_draw(fdf, index, index + 1, img);
		if (index / fdf->x_len != (fdf->y_len - 1))
			set_draw(fdf, index, index + fdf->x_len, img);
		index++;
	}
	return (NO_ERROR);
}
