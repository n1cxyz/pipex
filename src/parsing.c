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

void    ft_get_paths(t_var *var, char **envp)
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
	{
		perror("path split\n"); // paths[/../../..][/bin/][NULL]
		exit (EXIT_FAILURE);
	}
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
	{
		perror("cmd split\n"); // args[ls][-l][NULL]
		exit (EXIT_FAILURE);
	}
	free (arg_1);
}