/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/06 19:49:20 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void drawline(int x1, int y1, int x2, int y2, t_data *img)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

	static int draw = 0;
	// static size_t i = 0;
    int error = dx - dy;
	printf("%d:(%d:%d) - (%d:%d)\n", draw,x1,y1,x2,y2);
    while (1)
	{
        // 描画処理（ここでは単に表示しますが、実際のアプリケーションでは描画関数を使用してください）
        // printf("[countcall:%d]{%zu}(%d, %d)\n", draw,i++, x1, y1);
		my_mlx_pixel_put(img, x1, y1, 0x00FFFFFF);	
        if ((x1 >= 1000 || y1 >= 1000)||(x1 == x2 && y1 == y2)) 
		{
            break;
        }

        int e2 = 2 * error;

        if (e2 > -dy) {
            error = error - dy;
            x1 = x1 + sx;
        }

        if (e2 < dx) {
            error = error + dx;
            y1 = y1 + sy;
        }
    }
	draw++;
}

int	draw_wireframe(t_info *fdf, t_data *img)
{
	int	tmp_x;
	int	tmp_y;
	int	points;

	points = 0;
	while (points < fdf->points)
	{
		tmp_x = fdf->xyz[points].x;
		tmp_y = fdf->xyz[points].y;
		if ((points + 1) % fdf->x_len != 0)
			drawline(tmp_x, tmp_y, fdf->xyz[points + 1].x, fdf->xyz[points + 1].y, img);
		if (points / fdf->x_len != (fdf->y_len - 1))
			drawline(tmp_x, tmp_y, fdf->xyz[points + fdf->x_len].x, fdf->xyz[points + fdf->x_len].y, img);
		points++;
		// printf("[%d][%d]\n", points, fdf->points);
	}
	return (NO_ERROR);
}
