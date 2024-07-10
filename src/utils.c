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
		free(var->paths[i]);
		i++;
	}
	free(var->paths);
	i = 0;
	while (var->args[i])
	{
		free(var->args[i]);
		i++;
	}
	free(var->args);
    free(var->cmd_path);
}

void    ft_error_exit(char *message)
{
    perror("message");
	exit(EXIT_FAILURE);
}

void    ft_open_files(t_var *var, char *infile, char *outfile)
{
    if (access(infile, R_OK));
    {
        var->input_fd = open(infile, O_RDONLY);
        if (!var->input_fd)
            ft_error_exit("error\nopening input_fd\n");
    }
    if (access(outfile, W_OK));
    {
        var->input_fd = open(infile, O_WRONLY);
        if (!var->input_fd)
            ft_error_exit("error\nopening output_fd\n");
    }
}