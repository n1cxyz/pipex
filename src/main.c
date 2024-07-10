/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:57:16 by dasal             #+#    #+#             */
/*   Updated: 2024/07/08 13:57:18 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(t_var *var, char const **envp)
{
	int		pipefd[2];
	pid_t	pid;

	printf("help");
	if (pipe(pipefd) == -1)
		ft_error_exit("error\npipe\n");
	pid = fork();
	if (pid == -1)
		ft_error_exit("error\nfork\n");
	else if (pid == 0)
	{
		close(pipefd[0]);
		//dup2(pipefd[1], STDOUT_FILENO);
		execve(var->cmd_path, var->args, envp);
		ft_error_exit("error\nexecve\n");
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
	}
}
//execve(path, var.args, envp);
int main(int ac, char **av, char const **envp)
{
	t_var	var;
	
	ft_open_files(&var, av[1], av[4]); // close needed
	ft_get_paths(&var, envp);
	ft_get_args(&var, av[1], av[2]);
	if(!(ft_get_cmd_path(&var)))
	{
		ft_free_all(&var);
		ft_error_exit("error\ncmd not found\n");
	} // what happens if cmd not found?
	ft_exec(&var, envp);
	ft_free_all(&var);
	return 0;
}