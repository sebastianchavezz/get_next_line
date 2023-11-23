/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schavez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:14:35 by schavez           #+#    #+#             */
/*   Updated: 2023/11/22 17:14:50 by schavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	if (c == 0)
	{
		i = ft_strlen((char *)s);
		return (&s[i]);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
    size_t i = 0;
    while (i < size - 1 && src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return ft_strlen(src);	
}

char	*ft_strjoin(char  *s1, char  *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;
	char	*new_str;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	new_str = (char *)malloc(1 + total_len  * sizeof(char));
	if (new_str == NULL)
		return (NULL);
    ft_strlcpy(new_str, s1, s1_len + s2_len + 1);
    ft_strlcpy(new_str + s1_len, s2, s2_len + 1);
	free(s1);
	return (new_str);
}
