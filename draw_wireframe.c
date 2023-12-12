/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:03:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/12 16:07:37 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(x >= WIDTH || y >= HEIGHT) || (x < 0 || y < 0))
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static void	drawline(t_lineinfo line, t_data *img)
{
	int dx = abs(line.end_x - line.start_x);
	int dy = abs(line.end_y - line.start_y);
	int	sx = (line.start_x < line.end_x) ? 1 : -1;
	int	sy = (line.start_y < line.end_y) ? 1 : -1;
	int	tmp;

    int error = dx - dy;
    int steps = (dx > dy) ? dx : dy; // Determine the number of steps based on the longer axis

	steps++;
	tmp = 1;
	if (line.end_z - line.start_z < 0)
	{
		tmp = line.start_color;
		line.start_color = line.end_color;
		line.end_color = tmp;
		tmp = -1;
	}
    uint32_t current_color = line.start_color;
	if (steps == 0)
		return ;
	
	int color_step_r = (((line.end_color >> 16) & 0xFF) - ((line.start_color >> 16) & 0xFF) + 1) / (steps);
	int color_step_g = (((line.end_color >> 8) & 0xFF) - ((line.start_color >> 8) & 0xFF) + 1) / (steps);
	int color_step_b = ((line.end_color & 0xFF) - (line.start_color & 0xFF) + 1) / (steps);
	int i;
	i = 0;
    while(i++ < steps)
    {
        // if (!(line.start_x >= WIDTH || line.start_y >= HEIGHT) ||(line.start_x == line.end_x && line.start_y == line.end_y) || (line.start_x < 0 || line.start_y < 0))
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
