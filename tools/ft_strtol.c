/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:06:02 by atabout           #+#    #+#             */
/*   Updated: 2021/11/09 15:06:03 by atabout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	_strtol(const char *s)
{
	long	acc;
	int		c;

	c = s[2];
	s += 3;
	acc = 0;
	while (1)
	{
		if (ft_isdigit(c))
			c -= '0';
		else if (ft_isalpha(c))
		{
			if (isupper(c))
				c -= 'A' - 10;
			else
				c -= 'a' - 10;
		}
		else
			break ;
		acc *= 16;
		acc += c;
		c = (unsigned char) *s++;
	}
	return (acc);
}
