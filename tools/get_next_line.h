/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabout <atabout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:44:34 by atabout           #+#    #+#             */
/*   Updated: 2020/02/08 01:27:46 by atabout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

char	*ft_strjoin(char *s1, char *s2);
int		ft_readline(int fd, char **line, char *remains);
int		get_next_line(int fd, char **line);
size_t	ft_strcpy(char *dst, const char *src);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_double_free(char *s1, char *s2, int rd);
int		ft_nl_check(char *buff);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strjoin_freed(char *s1, char *s2, int option);
#endif
