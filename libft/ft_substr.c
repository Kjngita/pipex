/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:17:33 by gita              #+#    #+#             */
/*   Updated: 2025/05/03 17:51:44 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates memory (using malloc(3)) and returns a
substring from the string ’s’.
The substring starts at index ’start’ and has a
maximum length of ’len’. */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*baby;

	if (s == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	baby = malloc((len + 1) * sizeof(char));
	if (baby == NULL)
		return (NULL);
	baby = ft_memcpy(baby, s + start, len);
	baby[len] = '\0';
	return (baby);
}
