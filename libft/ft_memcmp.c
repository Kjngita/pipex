/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:27:26 by gita              #+#    #+#             */
/*   Updated: 2025/04/24 15:13:48 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*first;
	const unsigned char	*second;
	size_t				i;

	first = (const unsigned char *)s1;
	second = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (first[i] != second[i])
			return ((first[i] - second[i]));
		i++;
	}
	return (0);
}
