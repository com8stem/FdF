/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/04 22:21:59 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	drawline(int x1, int y1, int x2, int y2, t_data *img)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	error = dx - dy;
	while (1)
	{
		// 描画処理（ここでは単に表示しますが、実際のアプリケーションでは描画関数を使用してください）
		// printf("(%d, %d)\n", x1, y1);
		my_mlx_pixel_put(img, x1, y1, 0x00FFFFFF);
		if ((x1 >= x2 && y1 >= y2) || (x1 >= 1000 && y1 >= 1000))
		{
			break ;
		}
		e2 = 2 * error;
		if (e2 > -dy)
		{
			error = error - dy;
			x1 = x1 + sx;
		}
		if (e2 < dx)
		{
			error = error + dx;
			y1 = y1 + sy;
		}
	}
}

#define INIMV 300
#define ENLRATE 25

int	draw_wireframe(t_info *fdf, t_data *img)
{
	int tmp_x;
	int tmp_y;
	int points;

	points = 0;
	while (points < fdf->points)
	{
		tmp_x = fdf->xyz[points].x;
		tmp_y = fdf->xyz[points].y;
		if ((points + 1) % fdf->x_len != 0)
			drawline((tmp_x * ENLRATE) + INIMV, (tmp_y * ENLRATE) + INIMV,
				(fdf->xyz[points + 1].x * ENLRATE) + INIMV, (fdf->xyz[points
					+ 1].y * ENLRATE) + INIMV, img);
		if ((points + 1) / fdf->x_len != fdf->y_len - 1)
			drawline((tmp_x * ENLRATE) + INIMV, (tmp_y * ENLRATE) + INIMV,
				(fdf->xyz[points + fdf->x_len].x * ENLRATE) + INIMV,
				(fdf->xyz[points + fdf->x_len].y * ENLRATE) + INIMV, img);
		points++;
		printf("[%d][%d]\n", points, fdf->points);
	}

	// y = 0;
	// while (y + 1 < fdf->y_len)
	// {
	// 	x = 0;
	// 	while (x + 1 < fdf->x_len)
	// 	{
	// 		drawline(fdf->xyz[points].x, fdf->xyz[points].y,
	// 				fdf->xyz[points + 1].x, fdf->xyz[points + 1].y);
	// 		if (x + 2 < fdf->x_len)
	// 			drawline(fdf->xyz[points].x, fdf->xyz[points].y,
	// 					fdf->xyz[points + fdf->x_len].x, fdf->xyz[points + fdf->y_len].y);
	// 		x++;
	// 		points++;
	// 	}
	// 	y++;
	// 	points++;
	// }
	printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	fflush(stdout);
	return (NO_ERROR);
}