/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mapinfo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:02:59 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/05 21:49:02 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_splited(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free (ptr);
}

int	read_map(t_info *fdf, int map_fd)
{
	char	*oneline;
	char	**splitedline;
	int		x;
	int		y;

	y = 0;
	fdf->map_int = (int **)malloc((fdf->y_len) * sizeof(int *));
	if (fdf->map_int == NULL)
		ft_put_originalerror("failed to allocate memory!");
	while (y < fdf->y_len)
	{
		oneline = get_next_line_copy(map_fd);//___2
		splitedline = ft_split(oneline, ' ');
		if (splitedline == NULL)
			ft_put_originalerror("failed to read the map!");
		x = 0;
		fdf->map_int[y] = (int *)malloc((fdf->x_len) * sizeof(int));
		if (fdf->map_int[y] == NULL)
			ft_put_originalerror("failed to allocate memory!");
		while (x < fdf->x_len)
		{
			fdf->map_int[y][x] = ft_atoi(splitedline[x]);
			x++;
		}
		y++;
		free(oneline);
		ft_free_splited(splitedline);
	}
	return (NO_ERROR);
}

void	set_coordinates(t_info *fdf)
{
	int	x;
	int	y;
	int	points;

	points = 0;
	y = 0;
	fdf->xyz = (t_coordinates *)malloc(((fdf->x_len) * (fdf->y_len)) * sizeof(t_coordinates));
	if (fdf->xyz == NULL)
		ft_put_originalerror("failed to allocate!");
	while (y < fdf->y_len)
	{
		x = 0;
		while (x < fdf->x_len)
		{
			// fdf->xyz[points].initial_x = x;
			// fdf->xyz[points].initial_y = y;
			fdf->xyz[points].x = x;
			fdf->xyz[points].y = y;
			fdf->xyz[points].z = fdf->map_int[y][x];
			// printf ("[%d][%d][%d]\n", x, y, fdf->xyz[points].z);
			// fflush(stdout);
			x++;
			points++;
		}
		y++;
	}
	fdf->points = points;
}

int	get_mapinfo(t_info *fdf, char *filename)
{
	int	map_fd;

	map_fd = open (filename, O_RDONLY);
	if (map_fd == -1)
		ft_put_systemerror("open");
	read_map(fdf, map_fd);
	set_coordinates(fdf);
	close(map_fd);
	return (NO_ERROR);
}
