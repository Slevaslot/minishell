/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:55:10 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 17:01:54 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	charcheck(char c, char *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	k = -1;
	j = ft_strlen(s1);
	while (charcheck(s1[i], (char *)set) == 1)
		i++;
	while (charcheck(s1[j - 1], (char *)set) == 1)
		j--;
	if (set == NULL || !s1)
		return (0);
	if (i >= j)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * j - i + 1);
	if (!str)
		return (NULL);
	while (++k + i < j)
		str[k] = s1[k + i];
	str[k] = '\0';
	return (str);
}
