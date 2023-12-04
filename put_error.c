/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:05:27 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/04 20:05:34 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_originalerror(char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_put_systemerror(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}