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
	int	j;

	i = 0;
	while (var->paths[i])
	{
		free(var->paths[i]);
		i++;
	}
	free(var->paths);
	i = 0;
	while (i < 2) //cmd_count
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
	free(var->cmd_path[0]);
	free(var->cmd_path[1]);

}

void    ft_error_exit(char *message)
{
	ft_putstr_fd(message, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void    ft_open_files(t_var *var, char *infile, char *outfile)
{
	if ((access(infile, R_OK)) == 0)
	{
		var->input_fd = open(infile, O_RDONLY);
		if (!var->input_fd)
			ft_error_exit("error\nopening input_fd\n");
	}
	else
		ft_error_exit("error\nNo such file or directory\n");
	if ((access(outfile, W_OK)) == 0)
	{
		var->output_fd = open(outfile, O_WRONLY);
		if (!var->output_fd)
			ft_error_exit("error\nopening output_fd\n");
	}
	else
		ft_error_exit("error\nNo such file or directory!\n");
}

void	ft_init_vars(t_var *var)
{
	var->args = malloc(sizeof(char **) * 2); // cmd_count
	var->cmd_path = malloc(sizeof(char *) * 2); // cmd_count
}