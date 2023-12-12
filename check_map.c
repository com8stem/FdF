/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:02:30 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/12 17:04:09 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_x_len(char **oneline_map)
{
	int	x_len;
	int	numstr_len;
	int	i;

	x_len = 0;
	while (oneline_map[x_len] != NULL)
	{
		numstr_len = ft_strlen(oneline_map[x_len]);
		i = 0;
		while (i < numstr_len)
		{
			if (ft_isdigit(oneline_map[x_len][i]) == 0 &&
				(i == 0 && oneline_map[x_len][i] != '-'))
				ft_put_originalerror("map is invalid!");
			i++;
		}
		x_len++;
	}
	return (x_len);
}

static void	set_len(char **splitedline, int *x_len, int *tmp_x_len, int *y_len)
{
	*tmp_x_len = count_x_len(splitedline);
	if (*y_len == 0)
		*x_len = *tmp_x_len;
	if (*y_len != 0 && *tmp_x_len != *x_len)
		ft_put_originalerror("map is invalid!");
	*x_len = *tmp_x_len;
}

static void	check_peroneline(t_info *fdf, int map_fd)
{
	char	*oneline;
	char	**splitedline;
	int		x_len;
	int		tmp_x_len;
	int		y_len;

	y_len = 0;
	fdf->color_flag = 0;
	while (1)
	{
		oneline = get_next_line(map_fd);
		if (oneline == NULL)
			break ;
		splitedline = ft_split(oneline, ' ');
		if (splitedline == NULL)
			ft_put_originalerror("malloc");
		set_len(splitedline, &x_len, &tmp_x_len, &y_len);
		if (ft_strchr(oneline, ',') != NULL)
			fdf->color_flag = 1;
		y_len++;
		ft_free_splited(splitedline, oneline);
	}
	fdf->x_len = x_len;
	fdf->y_len = y_len;
}

int	check_map(t_info *fdf, char *filename)
{
	int		map_fd;

	map_fd = open(filename, O_RDONLY);
	if (map_fd == -1)
		ft_put_systemerror("open");
	check_peroneline(fdf, map_fd);
	close (map_fd);
	return (NO_ERROR);
}
