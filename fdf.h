/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:01:21 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/12 14:47:25 by kishizu          ###   ########.fr       */
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

typedef struct s_coordinate
{
	double	x;
	double	y;
	double	z;
	double	ini_z;
	int		color;
}	t_coordinates;

typedef struct s_info
{
	int				**map_int;
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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

char	*get_next_line(int fd);
char	*get_next_line_copy(int fd);

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

int		draw_wireframe(t_info *fdf, t_data *img);

void	ft_free_splited(char **splittedline, char *oneline);


#endif