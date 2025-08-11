/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:47:43 by gita              #+#    #+#             */
/*   Updated: 2025/05/03 17:48:52 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Applies the function f to each character of the
string s, passing its index as the first argument
and the character itself as the second. A new
string is created (using malloc(3)) to store the
results from the successive applications of f. */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*phoenix;
	unsigned int	fire;

	fire = 0;
	if (!s || !f)
		return (NULL);
	phoenix = ft_calloc(ft_strlen(s) + 1, 1);
	if (phoenix == NULL)
		return (NULL);
	while (s[fire])
	{
		phoenix[fire] = f(fire, s[fire]);
		fire++;
	}
	return (phoenix);
}
