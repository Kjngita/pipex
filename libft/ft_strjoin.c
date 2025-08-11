/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:24:18 by gita              #+#    #+#             */
/*   Updated: 2025/05/05 12:21:32 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*team;

	team = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), 1);
	if (team == NULL)
		return (NULL);
	else
	{
		ft_memmove(team, s1, ft_strlen(s1));
		ft_strlcat(team, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	}
	return (team);
}
