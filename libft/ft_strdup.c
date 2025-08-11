/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:42:17 by gita              #+#    #+#             */
/*   Updated: 2025/04/24 20:57:47 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dumpster;
	size_t	length;
	size_t	i;

	length = ft_strlen(s);
	dumpster = malloc((length + 1) * sizeof(char));
	if (dumpster == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (s[i])
		{
			dumpster[i] = s[i];
			i++;
		}
		dumpster[i] = '\0';
	}
	return (dumpster);
}
