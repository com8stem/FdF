/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/05 22:36:26 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	drawline(int x0, int y0, int x1, int y1, t_data *img)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	int sx, sy;
	if (x0 < x1)
	{
		sx = 1;
	}
	else
	{
		sx = -1;
	}
	if (y0 < y1)
	{
		sy = 1;
	}
	else
	{
		sy = -1;
	}
	err = dx - dy;
	while (1)
	{
		// 描画処理（例: ピクセルの表示）
		// printf("(%d, %d)\n", x0, y0);
		my_mlx_pixel_put(img, x0, y0, 0x00FFFFFF);
		if (x0 >= x1 && y0 >= y1)
		{
			break ;
		}
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err = err - dy;
			x0 = x0 + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			y0 = y0 + sy;
		}
	}
}

#define INIMV 300
#define ENLRATE 20

int	draw_wireframe(t_info *fdf, t_data *img)
{
	int	tmp_x;
	int	tmp_y;
	int	points;

	points = 0;
	while (points < fdf->points)
	{
		tmp_x = fdf->xyz[points].x * ENLRATE;
		tmp_y = fdf->xyz[points].y * ENLRATE;
		if ((points + 1) % fdf->x_len != 0)
			drawline(tmp_x + INIMV, tmp_y + INIMV, (fdf->xyz[points + 1].x
					* ENLRATE) + INIMV, (fdf->xyz[points + 1].y * ENLRATE)
				+ INIMV, img);
		if ((points + 1) / fdf->x_len != (fdf->y_len))
			drawline(tmp_x + INIMV, tmp_y + INIMV, (fdf->xyz[points
					+ fdf->x_len].x * ENLRATE) + INIMV, (fdf->xyz[points
					+ fdf->x_len].y * ENLRATE) + INIMV, img);
		points++;
		printf("[%d][%d]\n", points, fdf->points);
	}
	return (NO_ERROR);
}
