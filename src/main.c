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

void	ft_exec1(t_var *var, char *envp[], int pipefd[2])
{
	pid_t	pid;

	if (var->input_fd > 0 && var->cmd_1 == 1)
	{
		pid = fork();
		if (pid == -1)
			ft_error_exit("error\nfirst fork\n", 1);
		if (pid == 0)
		{
			dup2(var->input_fd, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close(var->input_fd);
			close(pipefd[1]);
			execve(var->cmd_path[0], var->args[0], envp);
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		ft_putchar_fd('0', var->output_fd);
		ft_putchar_fd('\n', var->output_fd);
	}
}

void	ft_exec2(t_var *var, char *envp[], int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error_exit("error\nfirst fork\n", 1);
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close (pipefd[0]);
		dup2(var->output_fd, STDOUT_FILENO);
		close (var->output_fd);
		execve(var->cmd_path[1], var->args[1], envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close (pipefd[0]);
	}
}
/*


fix open fd's



*/
int	main(int ac, char *av[], char *envp[])
{
	t_var	var;
	int		pipefd[2];

	if (ac != 5)
		ft_error_exit("Wrong number of argument", 0);
	if (pipe(pipefd) == -1)
		ft_error_exit("pipe", 1);
	ft_init_vars(&var, ac, av, envp);
	ft_get_cmd_paths(&var);
	if ((var.cmd_count != var.to_count) && (var.cmd_1 != 0 || \
	var.to_count == 0))
	{
		ft_free_all(&var);
		ft_error_exit("error\ncmd2 not found\n", 127);
	}
	ft_exec1(&var, envp, pipefd);
	close(var.input_fd);
	close(pipefd[1]);
	if (var.cmd_1 == 1 && var.error == 1 && var.cmd_count == var.to_count)
		ft_exec2(&var, envp, pipefd);
	if (var.cmd_1 == 0)
		ft_putstr_fd("error\ncmd1 not found\n", STDOUT_FILENO);
	ft_free_all(&var);
	return (0);
}
