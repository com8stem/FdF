/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:05:26 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/11 19:08:23 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_splited(char **splittedline, char *oneline)
{
	int	i;

	free (oneline);
	i = 0;
	while (splittedline[i] != NULL)
	{
		free(splittedline[i]);
		i++;
	}
	free (splittedline);
}
