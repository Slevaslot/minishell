/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:54:39 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 16:57:47 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;
	size_t	h;

	if (elementCount >= SIZE_MAXOU || elementSize >= SIZE_MAXOU)
		return (NULL);
	h = elementCount * elementSize;
	ptr = malloc(h);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, h);
	return (ptr);
}
