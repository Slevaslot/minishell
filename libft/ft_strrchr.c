/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:29:02 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 17:01:39 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr( const char *string, int searchedChar )
{
	int		i;
	char	*str;

	str = (char *)string;
	i = ft_strlen(str);
	while (i > 0 && str[i] != (char)searchedChar)
	{
		if (str[i] == (char)searchedChar)
			return (&str[i]);
		i--;
	}
	if (str[i] == (char)searchedChar)
		return (&str[i]);
	return (NULL);
}
