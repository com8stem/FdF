/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:32:56 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/13 20:36:07 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_colordata(t_colordata *color,
	int start_color, int end_color, int steps)
{
	color->dred = (((end_color >> 16) & 0xFF)
			- ((start_color >> 16) & 0xFF) + 1) / (steps);
	color->dgreen = (((end_color >> 8) & 0xFF)
			- ((start_color >> 8) & 0xFF) + 1) / (steps);
	color->dblue = ((end_color & 0xFF)
			- (start_color & 0xFF) + 1) / (steps);
}

static void	renew_color(t_colordata *color, uint32_t *current_color)
{
	color->r = (*current_color >> 16) & 0xFF;
	color->g = (*current_color >> 8) & 0xFF;
	color->b = *current_color & 0xFF;
	color->r += color->dred;
	color->g += color->dgreen;
	color->b += color->dblue;
	*current_color = (color->r << 16) | (color->g << 8) | color->b;
}

static void	set_bresendata(t_bresendata *bresen, t_lineinfo line)
{
	bresen->dx = abs(line.end_x - line.start_x);
	bresen->dy = abs(line.end_y - line.start_y);
	if (line.start_x < line.end_x)
		bresen->sx = 1;
	else
		bresen->sx = -1;
	if (line.start_y < line.end_y)
		bresen->sy = 1;
	else
		bresen->sy = -1;
	bresen->error = bresen->dx - bresen->dy;
	if (bresen->dx > bresen->dy)
		bresen->steps = bresen->dx;
	else
		bresen->steps = bresen->dy;
}

static void	set_error(t_bresendata *bresen, t_lineinfo *line)
{
	if (bresen->e2 > -(bresen->dy))
	{
		bresen->error = bresen->error - (bresen->dy);
		line->start_x = line->start_x + (bresen->sx);
	}
	if (bresen->e2 < (bresen->dx))
	{
		bresen->error = bresen->error + bresen->dx;
		line->start_y = line->start_y + bresen->sy;
	}
}

void	drawline(t_lineinfo line, t_imgdata *img)
{
	t_bresendata	bresen;
	t_colordata		color;
	uint32_t		current_color;
	int				i;

	set_bresendata(&bresen, line);
	if (bresen.steps == 0)
		return ;
	current_color = line.start_color;
	get_colordata(&color, line.start_color, line.end_color, bresen.steps);
	i = 0;
	while (i++ < bresen.steps)
	{
		my_mlx_pixel_put(img, line.start_x, line.start_y, current_color);
		bresen.e2 = 2 * bresen.error;
		set_error(&bresen, &line);
		renew_color(&color, &current_color);
	}
}
