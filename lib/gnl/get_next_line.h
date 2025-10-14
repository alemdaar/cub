/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddadi <ahaddadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:45:39 by ahaddadi          #+#    #+#             */
/*   Updated: 2024/12/27 16:39:30 by ahaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*my_join(char *s1, char *s2);
char	*my_dup(char *s);
size_t	my_strlen(char *s);
char	*my_strchr(char *s, int c);
void	cp2nl(char **dst, char **src);

#endif
