/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 23:27:56 by gita              #+#    #+#             */
/*   Updated: 2025/05/07 15:09:11 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*newstring;
	unsigned char	replace;

	newstring = (unsigned char *)s;
	replace = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		newstring[i] = replace;
		i++;
	}
	return (s);
}
