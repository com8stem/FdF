// #include "fdf.h"

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// typedef struct	s_vars {
// 	void	*mlx;
// 	void	*win;
// }				t_vars;

// int	close(t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	t_vars	vars;
// 	t_data	img;
// 	int	i = 0;
// 	check_arg(argc, argv);
// 	check_map(argv[1]);

// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "FdF");
// 	img.img = mlx_new_image(vars.mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 			&img.endian);
// 	while (i < 200)
// 	{
// 		my_mlx_pixel_put(&img, i, i, 0x00FF0000);
// 		i++;
// 	}
// 	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
// 	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
// 	mlx_loop(vars.mlx);
// 	exit(EXIT_SUCCESS);
// }
