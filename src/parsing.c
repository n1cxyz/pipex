/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:49:46 by dasal             #+#    #+#             */
/*   Updated: 2024/07/10 10:49:47 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_paths(t_var *var, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	var->paths = ft_split(envp[i] + 5, ':');
	if (!var->paths)
		ft_error_exit("error\npath split\n", 1);
}

void	ft_get_args(t_var *var, char **av)
{
	int	i;

	i = 0;
	while (i < var->cmd_count)
	{
		var->args[i] = ft_split(av[i + 2], ' ');
		i++;
	}
}

void	ft_get_cmd_paths(t_var *var)
{
	int		i;
	int		j;
	char	*temp_path;

	i = 0;
	while (i < var->cmd_count)
	{
		j = 0;
		while (j < 10)
		{
			temp_path = ft_strjoin(var->paths[j], "/");
			var->cmd_path[i] = ft_strjoin(temp_path, var->args[i][0]);
			free(temp_path);
			if (access(var->cmd_path[i], X_OK) == 0)
			{
				if (i == 0)
					var->cmd_1 = 1;
				var->to_count++;
				break ;
			}
			if (j != 9)
				free(var->cmd_path[i]);
			j++;
		}
		i++;
	}
}
