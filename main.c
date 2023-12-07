/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:00:07 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/06 19:51:13 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	my_close(int keycode, t_vars *vars)
{
	(void)keycode;
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}


int	main(int argc, char **argv)
{
	t_info	fdf;
	t_vars	vars;
	// void	*mlx;
	// void	*mlx_win;
	t_data	img;

	check_argc(argc);
	check_filename(argv[1]);
	check_map(&fdf, argv[1]);
	get_mapinfo(&fdf, argv[1]);
	convert_coordinates(&fdf);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HAIGHT, "FdF");
	img.img = mlx_new_image(vars.mlx, WIDTH, HAIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//create_window(mlx, mlxwin, img);
	draw_wireframe(&fdf, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, my_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
