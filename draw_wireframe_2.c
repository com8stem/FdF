/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:32:56 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/12 20:48:47 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_colordata(t_colordata *color,
	int start_color, int end_color, int steps)
{
	color->color_step_r = (((end_color >> 16) & 0xFF)
			- ((start_color >> 16) & 0xFF) + 1) / (steps);
	color->color_step_g = (((end_color >> 8) & 0xFF)
			- ((start_color >> 8) & 0xFF) + 1) / (steps);
	color->color_step_b = ((end_color & 0xFF)
			- (start_color & 0xFF) + 1) / (steps);
}

static void	renew_color(t_colordata *color, uint32_t *current_color)
{
	color->r = (*current_color >> 16) & 0xFF;
	color->g = (*current_color >> 8) & 0xFF;
	color->b = *current_color & 0xFF;
	color->r += color->color_step_r;
	color->g += color->color_step_g;
	color->b += color->color_step_b;
	*current_color = (color->r << 16) | (color->g << 8) | color->b;
}

static void	set_bresendata(t_bresendata *data, t_lineinfo line)
{
	data->dx = abs(line.end_x - line.start_x);
	data->dy = abs(line.end_y - line.start_y);
	if (line.start_x < line.end_x)
		data->sx = 1;
	else
		data->sx = -1;
	if (line.start_y < line.end_y)
		data->sy = 1;
	else
		data->sy = -1;
	data->error = data->dx - data->dy;
	if (data->dx > data->dy)
		data->steps = data->dx;
	else
		data->steps = data->dy;
}

static void	set_error(t_bresendata *data, t_lineinfo *line)
{
	if (data->e2 > -(data->dy))
	{
		data->error = data->error - (data->dy);
		line->start_x = line->start_x + (data->sx);
	}
	if (data->e2 < (data->dx))
	{
		data->error = data->error + data->dx;
		line->start_y = line->start_y + data->sy;
	}
}

void	drawline(t_lineinfo line, t_data *img)
{
	t_bresendata	data;
	t_colordata		color;
	uint32_t		current_color;
	int				i;

	set_bresendata(&data, line);
	if (data.steps == 0)
		return ;
	current_color = line.start_color;
	get_colordata(&color, line.start_color, line.end_color, data.steps);
	i = 0;
	while (i++ < data.steps)
	{
		my_mlx_pixel_put(img, line.start_x, line.start_y, current_color);
		data.e2 = 2 * data.error;
		set_error(&data, &line);
		renew_color(&color, &current_color);
	}
}
