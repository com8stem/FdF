/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:01:21 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/13 22:06:40 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _USE_MATH_DEFINES

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "./libft/libft.h"
// #include <X11/X.h> // for Linux
// #include <X11/keysym.h> // for Linux

# define NO_ERROR 0
# define BUFFER_SIZE 10000

# define WIDTH 1000
# define HEIGHT 1000

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_R 15

typedef struct s_coordinate
{
	double	x;
	double	y;
	double	z;
	double	ini_x;
	double	ini_y;
	double	ini_z;
	int		color;
}	t_coordinates;

typedef struct s_info
{
	int				**map_tmp;
	t_coordinates	*xyz;
	int				x_len;
	int				y_len;
	int				*color;
	int				color_flag;
	int				min_x;
	int				min_y;
	int				min_z;
	int				max_x;
	int				max_y;
	int				max_z;
	int				points;
	double			move_x;
	double			move_y;
}	t_info;

typedef struct s_lineinfo
{
	int	start_x;
	int	start_y;
	int	start_z;
	int	end_x;
	int	end_y;
	int	end_z;
	int	start_color;
	int	end_color;
}	t_lineinfo;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imgdata;

typedef struct s_colordata
{
	int	dred;
	int	dgreen;
	int	dblue;
	int	r;
	int	g;
	int	b;
}	t_colordata;

typedef struct s_bresendata
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	steps;
	int	e2;
}	t_bresendata;

char	*get_next_line(int fd);
char	*get_next_line_second(int fd);

void	ft_put_originalerror(char *error);
void	ft_put_systemerror(char *error);

int		check_argc(int argc);
int		check_filename(char *filename);
int		check_map(t_info *fdf, char *filename);
int		get_mapinfo(t_info *fdf, char *filename);

int		convert_coordinates(t_info *fdf);
void	get_min_coordinates(t_info *fdf);
void	get_max_coordinates(t_info *fdf);

void	get_max_min_z_coordinates(t_info *fdf);

void	move_frame(t_info *fdf, double move_x, double move_y);
void	reset_draw(t_info *fdf);

int		draw_wireframe(t_info *fdf, t_imgdata *img);
void	drawline(t_lineinfo line, t_imgdata *img);
void	my_mlx_pixel_put(t_imgdata *data, int x, int y, int color);

void	ft_free_splited(char **splittedline, char *oneline);
void	free_mapint(t_info *fdf, int **map_int);

#endif