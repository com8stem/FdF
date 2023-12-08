/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/07 23:09:19 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void drawline(t_lineinfo line, t_data *img)
{
    int dx = abs(line.end_x - line.start_x);
    int dy = abs(line.end_y - line.start_y);
    int sx = (line.start_x < line.end_x) ? 1 : -1;
    int sy = (line.start_y < line.end_y) ? 1 : -1;

    int error = dx - dy;
    int steps = (dx > dy) ? dx : dy; // Determine the number of steps based on the longer axis

	float color_step_r = (float)((line.end_color >> 16 & 0xFF) - (line.start_color >> 16 & 0xFF)) / steps;
	float color_step_g = (float)((line.end_color >> 8 & 0xFF) - (line.start_color >> 8 & 0xFF)) / steps;
	float color_step_b = (float)((line.end_color & 0xFF) - (line.start_color & 0xFF)) / steps;
	if (line.dz < 0)
	{
		color_step_r = -1 * color_step_r;
		color_step_g = -1 * color_step_g;
		color_step_b = -1 * color_step_b;
	}
	
    int current_color = line.start_color;

	int i;
	i = 0;
    while(i++ < steps)
    {
        if ((line.start_x >= WIDTH || line.start_y >= HAIGHT) ||(line.start_x == line.end_x && line.start_y == line.end_y) || (line.start_x < 0 || line.start_y < 0))
        {
            break;
        }

        // 描画処理
        my_mlx_pixel_put(img, line.start_x, line.start_y, current_color);

        int e2 = 2 * error;

        if (e2 > -dy)
        {
            error = error - dy;
            line.start_x = line.start_x + sx;
        }

        if (e2 < dx)
        {
            error = error + dx;
            line.start_y = line.start_y + sy;
        }

        // Interpolate color
        int r = (current_color >> 16) & 0xFF;
        int g = (current_color >> 8) & 0xFF;
        int b = current_color & 0xFF;

        r += color_step_r;
        g += color_step_g;
        b += color_step_b;

        current_color = (r << 16) | (g << 8) | b;
    }
}


// void drawline(t_lineinfo line, t_data *img)
// {
//     int dx = abs(line.end_x - line.start_x);
//     int dy = abs(line.end_y - line.start_y);
//     int sx = (line.start_x < line.end_x) ? 1 : -1;
//     int sy = (line.start_y < line.end_y) ? 1 : -1;

//     int error = dx - dy;
//     while (1)
// 	{
//         if ((line.start_x >= WIDTH || line.start_y >= HAIGHT)||(line.start_x == line.end_x && line.start_y == line.end_y) || (line.start_x < 0 || line.start_y < 0)) 
// 		{
//             break;
//         }
//         // 描画処理（ここでは単に表示しますが、実際のアプリケーションでは描画関数を使用してください）
// 		if (line.start_color == 0 || line.end_color == 0)
// 			my_mlx_pixel_put(img, line.start_x, line.start_y, 0x00FFFFFF);
// 		else
// 			my_mlx_pixel_put(img, line.start_x, line.start_y, line.start_color);
//         int e2 = 2 * error;

//         if (e2 > -dy) {
//             error = error - dy;
//             line.start_x = line.start_x + sx;
//         }

//         if (e2 < dx) {
//             error = error + dx;
//             line.start_y = line.start_y + sy;
//         }
//     }
// }

int	draw_wireframe(t_info *fdf, t_data *img)
{
	t_lineinfo	tmp;
	// int	tmp_x;
	// int	tmp_y;
	int	index;

	index = 0;
	while (index < fdf->points)
	{
		tmp.start_x = fdf->xyz[index].x;
		tmp.start_y = fdf->xyz[index].y;
		tmp.start_color = fdf->xyz[index].color;
		if ((index + 1) % fdf->x_len != 0)
		{
			tmp.end_x = fdf->xyz[index + 1].x;
			tmp.end_y = fdf->xyz[index + 1].y;
			tmp.end_color = fdf->xyz[index + 1].color;
			tmp.dz = fdf->xyz[index + 1].ini_z - fdf->xyz[index].ini_z;
			drawline(tmp, img);
			//drawline(tmp_x, tmp_y, fdf->xyz[index + 1].x, fdf->xyz[index + 1].y, img);
		}
		if (index / fdf->x_len != (fdf->y_len - 1))
		{
			tmp.end_x = fdf->xyz[index + fdf->x_len].x;
			tmp.end_y = fdf->xyz[index + fdf->x_len].y;
			tmp.end_color = fdf->xyz[index + fdf->x_len].color;
			tmp.dz = fdf->xyz[index + fdf->x_len].ini_z - fdf->xyz[index].ini_z;
			drawline(tmp, img);		
			//drawline(tmp_x, tmp_y, fdf->xyz[index + fdf->x_len].x, fdf->xyz[index + fdf->x_len].y, img);
		}
		index++;
		printf("[%d][%d]\n", index, fdf->points);
	}
	return (NO_ERROR);
}
