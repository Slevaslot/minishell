/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:15:01 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 16:59:57 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *destination, const void *source, size_t size )
{
	size_t	i;

	if (!destination && !source)
	{
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		((unsigned char *) destination)[i] = ((const char *) source)[i];
		i++;
	}
	return (destination);
}
