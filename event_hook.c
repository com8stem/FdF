/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:31:41 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/15 17:32:41 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	x_close_win(void)
{
	exit(EXIT_SUCCESS);
	return (NO_ERROR);
}

int	judge_keycode(int keycode)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_PLUS || keycode == KEY_MINUS || keycode == KEY_R)
	{
		return (1);
	}
	return (0);
}

void	zoom_frame(int keycode, t_info *fdf)
{
	if (keycode == KEY_PLUS)
		enlarge_frame(fdf, 1.1, 1.1);
	else if (keycode == KEY_MINUS)
		enlarge_frame(fdf, 0.9, 0.9);
	get_inimovevalue(fdf);
	move_frame(fdf, fdf->move_x, fdf->move_y);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (judge_keycode(keycode))
	{
		ft_bzero(vars->img->addr,
			WIDTH * HEIGHT * (vars->img->bits_per_pixel / 8));
		if (keycode == KEY_UP)
			move_frame(vars->fdf, 0, -8);
		else if (keycode == KEY_DOWN)
			move_frame(vars->fdf, 0, 8);
		else if (keycode == KEY_LEFT)
			move_frame(vars->fdf, -8, 0);
		else if (keycode == KEY_RIGHT)
			move_frame(vars->fdf, 8, 0);
		else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
			zoom_frame(keycode, vars->fdf);
		else if (keycode == KEY_R)
			reset_draw(vars->fdf);
		draw_wireframe(vars->fdf, vars->img);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	return (NO_ERROR);
}

void	set_eventhook(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, key_hook, vars);
	mlx_hook(vars->win, 17, 1L << 17, x_close_win, NULL);
}
