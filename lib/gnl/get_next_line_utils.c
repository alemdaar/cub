/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddadi <ahaddadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:45:32 by ahaddadi          #+#    #+#             */
/*   Updated: 2024/12/27 16:32:43 by ahaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	my_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*my_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*s12;

	if (!s1)
		return (my_dup(s2));
	if (!s2)
		return (my_dup(s1));
	s12 = malloc(my_strlen(s1) + my_strlen(s2) + 1);
	if (!s12)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		s12[i++] = s1[j++];
	j = 0;
	while (s2[j])
		s12[i++] = s2[j++];
	s12[i] = 0;
	return (s12);
}

char	*my_dup(char *s)
{
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	i = 0;
	dup = malloc(my_strlen(s) + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*my_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	if ((char)c == 0)
		return (s + i);
	return (NULL);
}

void	cp2nl(char **dst, char **src)
{
	int	i;

	i = 0;
	if (*dst && *src)
	{
		while ((*src)[i] && (*src)[i] != '\n')
		{
			(*dst)[i] = (*src)[i];
			i++;
		}
		if ((*src)[i] == '\n')
			(*dst)[i++] = '\n';
		(*dst)[i] = 0;
	}
}
