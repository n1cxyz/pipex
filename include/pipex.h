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
	char	**paths;
	char	**args;

}	t_var;

void	ft_get_paths(t_var *var, char **envp);
void    ft_get_args(t_var *var, char *infile, char *cmd_1);
void	ft_free_all(t_var *var);