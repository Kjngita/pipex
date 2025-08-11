/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:06:14 by gita              #+#    #+#             */
/*   Updated: 2025/05/02 15:16:47 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	how_long_number_is(int num)
{
	int	step;

	step = 0;
	if (num <= 0)
		step += 1;
	while (num != 0)
	{
		num = num / 10;
		step++;
	}
	return (step);
}

char	*ft_itoa(int n)
{
	char	*vessel;
	int		length;
	int		sign;

	length = how_long_number_is(n);
	sign = 1;
	vessel = ft_calloc(length + 1, 1);
	if (vessel == NULL)
		return (NULL);
	if (n < 0)
		sign = -1;
	while (length != 0)
	{
		length--;
		vessel[length] = n % 10 * sign + '0';
		n = n / 10;
	}
	if (sign == -1)
		vessel[0] = '-';
	return (vessel);
}
