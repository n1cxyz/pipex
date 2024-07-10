/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:19:15 by dasal             #+#    #+#             */
/*   Updated: 2024/07/10 11:19:16 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_var *var)
{
    int i;

    i = 0;
	while (var->paths[i])
	{
		free (var->paths[i]);
		i++;
	}
	free (var->paths);
	i = 0;
	while (var->args[i])
	{
		free (var->args[i]);
		i++;
	}
	free (var->args);
}
