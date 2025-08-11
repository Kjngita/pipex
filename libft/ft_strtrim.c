/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:55:41 by gita              #+#    #+#             */
/*   Updated: 2025/04/28 16:06:01 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	head;
	size_t	tail;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	head = i;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == NULL)
			tail = i;
		i++;
	}
	return (ft_substr(s1, head, tail - head + 1));
}
