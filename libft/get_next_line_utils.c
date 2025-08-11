/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:42 by gita              #+#    #+#             */
/*   Updated: 2025/08/11 22:03:47 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*gnl_strchr(char *s, unsigned char c)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] || c == '\0')
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*duo;
	size_t	i;
	size_t	p;

	if (s2 == NULL)
		return (NULL);
	duo = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (duo == NULL)
		return (NULL);
	i = 0;
	while (i < gnl_strlen(s1))
	{
		duo[i] = s1[i];
		i++;
	}
	p = 0;
	while (s2[p])
		duo[i++] = s2[p++];
	duo[i] = '\0';
	return (duo);
}

char	*gnl_substr(char *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*babystr;

	if (str == NULL)
		return (NULL);
	if (len > (gnl_strlen(str) - start))
		len = gnl_strlen(str) - start;
	if (start > gnl_strlen(str))
		len = 0;
	babystr = malloc (len + 1);
	if (babystr == NULL)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		babystr[i++] = str[start++];
		len--;
	}
	babystr[i] = '\0';
	return (babystr);
}
