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

void    ft_get_paths(t_var *var, char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)// find PATH environment 
			break;
		i++;
	}
	var->paths = ft_split(envp[i] + 5, ':');
	if (!var->paths)
		ft_error_exit("error\npath split\n");	// paths[/../../..][/bin/][NULL]
}

void    ft_get_args(t_var *var, char **av)
{
	var->args[0] = ft_split(av[2], ' ');
	var->args[1] = ft_split(av[3], ' ');
}

int	ft_get_cmd_path(t_var *var, char *arg)
{
	int		i;
	char	*temp_path;

	i = 0;
	while (var->paths[i])
	{
		temp_path = ft_strjoin(var->paths[i], "/"); //find available command path /bin/ls
		var->cmd_path[var->j] = ft_strjoin(temp_path, arg);  //with access("/bin/ls", X_OK)
		free(temp_path);
		if (access(var->cmd_path[var->j], X_OK) == 0)
			return(1);
		free(var->cmd_path[var->j]);
		i++;
	}
	var->cmd_path[var->j] = NULL;
	ft_free_all(var);
	ft_error_exit("error\ncommand not found\n");
	return(0);
}