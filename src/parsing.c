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

void    ft_get_paths(t_var *var, char const **envp)
{
    int i;

    i = 0;
    while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0) //find PATH environment 
			break;
		i++;
	}
	var->paths = ft_split(envp[i] + 5, ':');
	if (!var->paths)
		ft_error_exit("error\npath split\n"); // paths[/../../..][/bin/][NULL]
}

void    ft_get_args(t_var *var, char *infile, char *cmd_1)
{
    char    *temp_arg_1;
    char    *arg_1;

    temp_arg_1 = ft_strjoin(cmd_1, " ");
	arg_1 = ft_strjoin(temp_arg_1, infile);
	free (temp_arg_1);
	var->args = ft_split(arg_1, ' ');
	if (!var->args)
		ft_error_exit("error\ncmd split\n"); // args[head][Makefile][NULL]
	free (arg_1);
}

int	ft_get_cmd_path(t_var *var)
{
	int		i;
	char	*temp_path;

	i = 0;
	while (var->paths[i])
	{
		temp_path = ft_strjoin(var->paths[i], "/"); //find available command path /bin/ls
		var->cmd_path = ft_strjoin(temp_path, var->args[0]);  //with access("/bin/ls", X_OK)
		free(temp_path);
		if (access(var->cmd_path, X_OK) == 0)
			return(1);
		free(var->cmd_path);
		i++;
	}
	return(0);
}