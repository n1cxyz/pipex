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
	int	i;
	int	j;

	i = 0;
	while (var->paths[i])
	{
		free(var->paths[i]);
		i++;
	}
	free(var->paths);
	i = 0;
	while (i < var->cmd_count)
	{
		free(var->cmd_path[i]);
		i++;
	}
	free(var->cmd_path);
	i = 0;
	while (i < var->cmd_count)
	{
		j = 0;
		while (var->args[i][j])
		{
			free(var->args[i][j]);
			j++;
		}
		free(var->args[i]);
		i++;
	}
	free(var->args);
}

void	ft_error_exit(char *message, int code)
{
	ft_putstr_fd(message, STDOUT_FILENO);
	exit(code);
}

void	ft_open_files(t_var *var, char *infile, char *outfile)
{
	var->input_fd = open(infile, O_RDONLY);
	if (var->input_fd < 0)
	{
		ft_putstr_fd("error\nno such file or directory\n", STDOUT_FILENO);
		var->error = -1;
	}
	var->output_fd = open(outfile, O_WRONLY | O_CREAT, 00777);
	if (var->output_fd < 0)
		ft_putstr_fd("error\nno such file or directory\n", STDOUT_FILENO);
}

void	ft_init_vars(t_var *var, int ac, char *av[], char *envp[])
{
	int	i;

	var->cmd_1 = 0;
	var->to_count = 0;
	var->error = 1;
	var->cmd_count = ac - 3;
	var->args = malloc(sizeof(char **) * var->cmd_count);
	var->cmd_path = malloc(sizeof(char *) * var->cmd_count);
	i = 0;
	while (i < var->cmd_count)
	{
		var->cmd_path[i] = NULL;
		i++;
	}
	ft_open_files(var, av[1], av[ac - 1]);
	ft_get_paths(var, envp);
	ft_get_args(var, av);
}
