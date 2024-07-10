/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:57:59 by dasal             #+#    #+#             */
/*   Updated: 2024/07/10 08:58:01 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfjoin(char *s1, char const *s2)
{
	char	*result;
	char	*result_ptr;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	result_ptr = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
    //free (s1);
	return (result_ptr);
}
