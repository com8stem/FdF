/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:00:07 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/11 22:08:51 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	my_close_win(int keycode, t_vars *vars)
{
	(void)keycode;
	(void)vars;
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	fdf;
	t_vars	vars;
	t_data	img;

	check_argc(argc);
	check_filename(argv[1]);
	check_map(&fdf, argv[1]);
	get_mapinfo(&fdf, argv[1]);
	convert_coordinates(&fdf);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FdF");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//create_window(mlx, mlxwin, img);
	draw_wireframe(&fdf, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_hook(vars.win, 33, 1L << 17, my_close_win, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
