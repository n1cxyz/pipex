/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:00:25 by dasal             #+#    #+#             */
/*   Updated: 2024/07/08 14:00:27 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"

typedef struct s_var
{
	int		j;
	int		input_fd;
	int		output_fd;
	int		cmd_count;
	char	**paths;
	char	***args;
	char	**cmd_path;
}	t_var;

//		parsing
void	ft_get_paths(t_var *var, char *envp[]);
void    ft_get_args(t_var *var, char **av);
int		ft_get_cmd_path(t_var *var, char *arg);
//		utils
void	ft_free_all(t_var *var);
void	ft_init_vars(t_var *var);
void    ft_open_files(t_var *var, char *infile, char *outfile);
void    ft_error_exit(char *message);