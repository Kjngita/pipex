/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:14:48 by gita              #+#    #+#             */
/*   Updated: 2025/08/11 22:10:32 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	writechar(unsigned int c)
{
	char	single;
	int		guard;

	single = (char)c;
	guard = write(1, &single, 1);
	if (guard == -1)
		return (-1);
	else
		return (1);
}

int	writestr(char *text)
{
	int	i;

	i = 0;
	if (text == NULL)
	{
		if (write (1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (text[i])
	{
		if (write(1, &text[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}
