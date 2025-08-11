/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:21:49 by gita              #+#    #+#             */
/*   Updated: 2025/04/24 15:11:46 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	q;

	i = 0;
	q = ft_strlen(dst);
	if (q >= size)
	{
		return (ft_strlen(src) + size);
	}
	else
	{
		while (src[i] && (q + i < (size - 1)))
		{
			dst[q + i] = src[i];
			i++;
		}
		dst[q + i] = '\0';
	}
	return (q + ft_strlen(src));
}
