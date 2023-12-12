/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mapinfo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:02:59 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/12 17:41:46 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_coordinates(t_info *fdf);

static void	prepare_fdf(t_info *fdf)
{
	fdf->color = (int *)malloc((fdf->x_len * fdf->y_len) * sizeof(int));
	if (fdf->color == NULL)
		ft_put_originalerror("malloc");
	fdf->map_int = (int **)malloc((fdf->y_len) * sizeof(int *));
	if (fdf->map_int == NULL)
		ft_put_originalerror("malloc");
}

static int	ft_atoi_color(const char *str)
{
	long	num;

	num = 0;
	while (*str != 'x')
		str++;
	str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			ft_put_originalerror("map is invalid!");
		str++;
	}
	while ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')
		|| (*str >= 'a' && *str <= 'f'))
	{
		if (*str >= '0' && *str <= '9')
			num = (16 * num) + (*str - '0');
		else if (*str >= 'A' && *str <= 'F')
			num = (16 * num) + (*str - 'A' + 10);
		else if (*str >= 'a' && *str <= 'f')
			num = (16 * num) + (*str - 'a' + 10);
		str++;
	}
	return ((int)num);
}

static void	set_mapinfo_tmp(t_info *fdf, char **splitedline, int x, int y)
{
	fdf->map_int[y][x] = ft_atoi(splitedline[x]);
	if (ft_strchr(splitedline[x], ',') != NULL)
		fdf->color[x + fdf->x_len * y] = ft_atoi_color(splitedline[x]);
	else
		fdf->color[x + fdf->x_len * y] = 0x888888;
}

static void	read_map(t_info *fdf, int map_fd)
{
	char	*oneline;
	char	**splitedline;
	int		x;
	int		y;

	y = 0;
	prepare_fdf(fdf);
	while (y < fdf->y_len)
	{
		oneline = get_next_line_second(map_fd);
		splitedline = ft_split(oneline, ' ');
		if (splitedline == NULL)
			ft_put_originalerror("failed to read the map!");
		fdf->map_int[y] = (int *)malloc((fdf->x_len) * sizeof(int));
		if (fdf->map_int[y] == NULL)
			ft_put_originalerror("malloc");
		x = 0;
		while (x < fdf->x_len)
		{
			set_mapinfo_tmp(fdf, splitedline, x, y);
			x++;
		}
		y++;
		ft_free_splited(splitedline, oneline);
	}
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
