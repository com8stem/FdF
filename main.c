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

int	main(int argc, char **argv)
{
	t_info	fdf;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	check_argc(argc);
	check_filename(argv[1]);
	check_map(&fdf, argv[1]);
	get_mapinfo(&fdf, argv[1]);
	convert_coordinates(&fdf);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1000, "FdF");
	img.img = mlx_new_image(mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//create_window(mlx, mlxwin, img);
	draw_wireframe(&fdf, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
