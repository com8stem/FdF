/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/13 20:33:14 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_imgdata *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= WIDTH || y >= HEIGHT) || (x < 0 || y < 0))
	{
		dst = img->addr + (y * img->line_length + x
				* (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static void	set_drawinfo(t_info *fdf, int start_i, int end_i, t_imgdata *img)
{
	t_lineinfo	tmp;

	tmp.start_x = fdf->xyz[start_i].x;
	tmp.start_y = fdf->xyz[start_i].y;
	tmp.start_color = 0xFFFFFF;
	tmp.end_x = fdf->xyz[end_i].x;
	tmp.end_y = fdf->xyz[end_i].y;
	tmp.end_color = 0xFFFFFF;
	if (fdf->color_flag == 1)
	{
		tmp.start_color = fdf->xyz[start_i].color;
		tmp.end_color = fdf->xyz[end_i].color;
	}
	tmp.start_z = fdf->xyz[start_i].ini_z;
	tmp.end_z = fdf->xyz[end_i].ini_z;
	drawline(tmp, img);
}

int	draw_wireframe(t_info *fdf, t_imgdata *img)
{
	int			index;

	index = 0;
	while (index < fdf->points)
	{
		if ((index + 1) % fdf->x_len != 0)
			set_drawinfo(fdf, index, index + 1, img);
		if (index / fdf->x_len != (fdf->y_len - 1))
			set_drawinfo(fdf, index, index + fdf->x_len, img);
		index++;
	}
	return (NO_ERROR);
}
