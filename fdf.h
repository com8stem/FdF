/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:01:21 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/04 22:19:11 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _USE_MATH_DEFINES

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "./libft/libft.h"
// #include <X11/X.h> // for Linux
// #include <X11/keysym.h> // for Linux

# define NO_ERROR 0
# define BUFFER_SIZE 100

typedef struct s_coordinate
{
	int	x;
	int	y;
	int	z;
}	t_coordinates;

typedef struct s_info
{
	int				**map_int;
	t_coordinates	*xyz;
	int				x_len;
	int				y_len;
	int				points;
}	t_info;

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
int		create_window(void *mlx, void *mlxwin);
int		draw_wireframe(t_info *fdf, t_data *img);

#endif