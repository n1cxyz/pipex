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
	int		input_fd;
	int		output_fd;
	int		cmd_count;
	int		to_count;
	char	**paths;
	char	***args;
	char	**cmd_path;
	char	*temp_path;
	int		error;
	int		cmd_1;
}	t_var;

//		parsing
void	ft_get_paths(t_var *var, char *envp[]);
void	ft_get_args(t_var *var, char **av);
void	ft_get_cmd_paths(t_var *var);
//		utils
void	ft_free_all(t_var *var);
void	ft_free_args(t_var *var);
void	ft_init_vars(t_var *var, int ac, char *av[], char *envp[]);
void	ft_open_files(t_var *var, char *infile, char *outfile);
void	ft_error_exit(char *message, int code);
