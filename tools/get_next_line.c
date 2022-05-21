/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabout <atabout@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:19:13 by atabout           #+#    #+#             */
/*   Updated: 2020/02/08 01:16:31 by atabout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** 1. read() buff isn't guaranteed to be NULL terminated
** 2. ft_str_join_freed is set to free either 1st ptr, 2nd or both
** 		-> to easily precise the heap allocated memory to be freed
** 3. ft_double_free is to free 2 diff ptrs, set them to NULL for safety,
**		-> and return the return :))
** 4. OPEN_MAX is defined on limits.h, in some distrubtions OPEN_MAX
**		-> then its set to 10240
*/

int		ft_double_free(char *s1, char *s2, int rd)
{
	if (s1 != NULL)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2 != NULL)
	{
		free(s2);
		s2 = NULL;
	}
	return (rd);
}

int		ft_nl_check(char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\n')
		if (str[i] == '\0')
			return (-1);
	return (i);
}

char	*ft_strjoin_freed(char *s1, char *s2, int option)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	if (option == 1 || option == 3)
	{
		free(s1);
		s1 = NULL;
	}
	if (option == 2 || option == 3)
	{
		free(s2);
		s2 = NULL;
	}
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	static char		remains[OPEN_MAX][BUFFER_SIZE + 1];
	int				i;

	if (fd < 0 || fd > OPEN_MAX || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if ((*line = ft_strdup("")) == NULL)
		return (-1);
	if (remains[fd][0] == '\0')
		return (ft_readline(fd, line, remains[fd]));
	if ((i = ft_nl_check(remains[fd])) != -1)
	{
		free(*line);
		if ((*line = malloc(sizeof(**line) * (i + 1))) == NULL)
			return (-1);
		ft_strncpy(*line, remains[fd], i);
		(*line)[i] = '\0';
		ft_strcpy(remains[fd], remains[fd] + i + 1);
		return (1);
	}
	free(*line);
	if ((*line = malloc(sizeof(**line) * (ft_strlen(remains[fd]) + 1))) == NULL)
		return (-1);
	ft_strcpy(*line, remains[fd]);
	remains[fd][0] = '\0';
	return (ft_readline(fd, line, remains[fd]));
}

int		ft_readline(int fd, char **line, char *remains)
{
	int		rt;
	char	*buff;

	if ((buff = malloc(sizeof(*buff) * (BUFFER_SIZE + 1))) == NULL)
		return (ft_double_free(*line, NULL, -1));
	while ((rt = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[rt] = '\0';
		if ((rt = ft_nl_check(buff)) != -1)
		{
			ft_strcpy(remains, buff + rt + 1);
			buff[rt] = '\0';
			if ((*line = ft_strjoin_freed(*line, buff, 1)) == NULL)
				return (ft_double_free(buff, NULL, -1));
			return (ft_double_free(buff, NULL, 1));
		}
		if ((*line = ft_strjoin_freed(*line, buff, 1)) == NULL)
			return (ft_double_free(buff, NULL, -1));
	}
	if (rt == -1)
		return (ft_double_free(buff, *line, -1));
	return (ft_double_free(buff, NULL, rt));
}
