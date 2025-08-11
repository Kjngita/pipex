/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:55:32 by gita              #+#    #+#             */
/*   Updated: 2025/05/07 15:12:10 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return a pointer to the last occurrence of char c or NULL
if the character is not found. The terminating null byte is
considered part of the string, so that if c is specified as '\0',
function returns a pointer to the terminator */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*moonwalk;
	int		i;

	moonwalk = (char *)s;
	i = ft_strlen(moonwalk);
	while (i >= 0)
	{
		if (moonwalk[i] == (unsigned char)c || c == 0)
			return (moonwalk + i);
		i--;
	}
	return (NULL);
}
