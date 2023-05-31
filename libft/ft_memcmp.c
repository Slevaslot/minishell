/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:34 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 16:59:48 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*str1;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	str = (unsigned char *)s1;
	str1 = (unsigned char *)s2;
	while (str[i] == str1[i] && i < n - 1)
	{
		i++;
	}
	if (str[i] == str1[i])
		return (0);
	return ((int)(str[i] - str1[i]));
}
