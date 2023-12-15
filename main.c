/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:00:07 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/15 19:09:07 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_window(t_vars *vars, t_imgdata *img)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (NO_ERROR);
}

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
