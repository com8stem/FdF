/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:00:07 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/13 22:06:52 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_info		*fdf;
	t_imgdata	*img;
}	t_vars;

int	x_close_win(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_R)
	{
		ft_bzero(vars->img->addr,
			WIDTH * HEIGHT * (vars->img->bits_per_pixel / 8));
		if (keycode == KEY_UP)
			move_frame(vars->fdf, 0, -3);
		else if (keycode == KEY_DOWN)
			move_frame(vars->fdf, 0, 3);
		else if (keycode == KEY_LEFT)
			move_frame(vars->fdf, -3, 0);
		else if (keycode == KEY_RIGHT)
			move_frame(vars->fdf, 3, 0);
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
	return (0);
}

int	create_window(t_vars *vars, t_imgdata *img)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (NO_ERROR);
}

void	set_eventhook(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, key_hook, vars);
	mlx_hook(vars->win, 17, 1L << 17, x_close_win, NULL);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q fdf");
// }

int	main(int argc, char **argv)
{
	t_info		fdf;
	t_vars		vars;
	t_imgdata	img;

	vars.fdf = &fdf;
	vars.img = &img;
	check_argc(argc);
	check_filename(argv[1]);
	check_map(&fdf, argv[1]);
	get_mapinfo(&fdf, argv[1]);
	convert_coordinates(&fdf);
	create_window(&vars, &img);
	draw_wireframe(&fdf, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	set_eventhook(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
