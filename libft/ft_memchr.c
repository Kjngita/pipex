/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:19:47 by gita              #+#    #+#             */
/*   Updated: 2025/05/03 17:29:57 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Scans the initial n bytes of the memory area pointed to by s for the
first instance of c. Both c and the bytes of the memory area pointed to
by s are interpreted as unsigned char.
	Return a pointer to the matching byte or NULL if the character
	does not occur in the given memory area */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*pnt;
	unsigned char	rock;
	size_t			i;

	pnt = (unsigned char *)s;
	rock = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (pnt[i] == rock)
			return (pnt + i);
		i++;
	}
	return (NULL);
}
