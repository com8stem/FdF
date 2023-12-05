/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:46:35 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/05 20:33:11 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int num)
{
	int		digits;
	long	n;

	digits = 0;
	n = (long)num;
	if (num < 0)
	{
		n = -n;
		digits++;
	}
	while (n >= 10)
	{
		n = n / 10;
		digits++;
	}
	return (digits + 1);
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*result;
	long	num;

	num = (long)n;
	if (n == 0)
		return (ft_strdup("0"));
	digits = count_digits(n);
	if (n < 0)
		num = -num;
	result = (char *)malloc((digits + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[digits--] = '\0';
	while (num > 0)
	{
		result[digits--] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
