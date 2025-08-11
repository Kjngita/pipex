/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:52:18 by gita              #+#    #+#             */
/*   Updated: 2025/04/24 15:13:02 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*sea;
	char	*fish;
	size_t	i;
	size_t	j;

	sea = (char *)big;
	fish = (char *)little;
	i = 0;
	j = 0;
	if (fish[j] == 0)
		return (sea);
	while (sea[i] != 0 && i < len)
	{
		j = 0;
		while (sea[i + j] == fish[j] && j < len - i)
		{
			if (fish[j + 1] == 0)
				return (sea + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
