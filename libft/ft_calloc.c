/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:32:23 by gita              #+#    #+#             */
/*   Updated: 2025/04/24 16:17:32 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			ruler;
	unsigned char	*new;

	ruler = nmemb * size;
	if (ruler != 0 && (ruler / nmemb) != size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		ruler = 1;
	new = malloc(ruler);
	if (new != NULL)
		ft_bzero(new, ruler);
	return (new);
}
