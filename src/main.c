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


void	ft_exec(t_var *var, char **args, char *envp[])
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		ft_error_exit("error\npipe\n");
	pid1 = fork();
	if (pid1 == -1)
		ft_error_exit("error\nfirst fork\n");
	else if (pid1 == 0)
	{
		if (dup2(var->input_fd, STDIN_FILENO) == -1)
			ft_error_exit("dup2 input_fd");
		close(var->input_fd);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			ft_error_exit("dup2 pipefd");
		close(pipefd[0]);
        close(pipefd[1]);
		execve(var->cmd_path[0], args, envp);
		ft_error_exit("error\nexecve1\n");
	}
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_error_exit("error\nfirst fork\n");
		else if (pid2 == 0)
		{
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
				ft_error_exit("dup2 pipefd[0]");
			if (dup2(var->output_fd, STDOUT_FILENO) == -1)
				ft_error_exit("dup2 outputfd");
			close(pipefd[0]);
			close(pipefd[1]);
			execve(var->cmd_path[1], var->args[1], envp);
			ft_error_exit("error\nexecve1\n");
		}
		else
			close(pipefd[0]);
			close(pipefd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
	}
}

int main(int ac, char *av[], char *envp[])
{
	t_var		var;

	var.j = 0;

	var.cmd_count = ac - 3; // not working yet
	ft_init_vars(&var);
	ft_open_files(&var, av[1], av[ac - 1]); // close needed
	ft_get_paths(&var, envp);
	ft_get_args(&var, av);
	ft_get_cmd_path(&var, var.args[0][0]);
	var.j++;
	ft_get_cmd_path(&var, var.args[1][0]);
	// what happens if file not found?
	ft_exec(&var, var.args[0], envp);
	//ft_exec(&var, var.args[1], envp);
	ft_free_all(&var);
	return 0;
}