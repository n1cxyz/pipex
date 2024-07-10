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

//access("/bin/ls", X_OK)
/*
char *args[3];

args[0] = "ls";
args[1] = "-m";
args[2] = NULL;
execve("/bin/ls", args, NULL);
*/
int main(int ac, char **av, char **envp)
{
	t_var	var;
	int		i;
	char	*path;
	char	*temp_path;
	
	ft_get_paths(&var, envp);
	ft_get_args(&var, av[1], av[2]);

	i = 0;
	while (var.paths[i])
	{
		temp_path = ft_strjoin(var.paths[i], "/"); //find available command path /bin/ls
		path = ft_strjoin(temp_path, var.args[0]);  //with access("/bin/ls", X_OK)
		free(temp_path);
		if (access(path, X_OK) == 0)
			execve(path, var.args, envp);
		free (path);
		i++;
	}
	perror("Error\ncommand not found\n");

	ft_free_all(&var);
	
	return 0;
}
/* int	main()
{
	char *args[3];
 
	args[0] = "ls";
	args[1] = "-a";
	args[2] = NULL;
	execve("/bin/ls", args, NULL);
	printf("This line will not be executed.\n");
 
	return (0);
} */

/* int	main(int ac, char **av)
{
	int 	pipefd[2];
	pid_t	pid;
	char	buffer[1024];
	ssize_t	bytes_read, bytes_written;
	int		input_fd;
	int		output_fd;

	
	if (ac != 3)
	{
		printf("Usage: %s <input file> <output file>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		printf("pipe\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("fork\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pipefd[1]);

		output_fd = open(av[2], O_WRONLY);
		if (output_fd == -1)
		{
			printf("output_fd");
			exit(EXIT_FAILURE);
		}
		while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
		{
			bytes_written = write(output_fd, buffer, bytes_read);
			if (bytes_written == -1)
			{
				perror("write to output file");
				close(output_fd);
				exit(EXIT_FAILURE);
			}
		}
		close(output_fd);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		input_fd = open(av[1], O_RDONLY);
		if (input_fd == -1)
		{
			printf("input_fd\n");
			exit(EXIT_FAILURE);
		}
		bytes_read = read(input_fd, buffer, sizeof(buffer) - 1);
		if (bytes_read == -1)
		{
			printf("bytes_read_parent");
			exit(EXIT_FAILURE);
		}
		buffer[bytes_read] = '\0';
		bytes_written = write(pipefd[1], buffer, bytes_read);
		if (bytes_written == -1)
		{
			printf("bytes_written_parent\n");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
		close(pipefd[1]);
		//wait(NULL);
	}
	return (0);
} */

/* int	main(int ac, char **av)
{
	(void) ac;
	char *envp[] = {NULL};
	char *argv[3];
	
	if (ac == 2)
	{
		if (ft_strncmp(av[1], "ls", 2) == 0)
		{
			argv[0] = "ls";
			argv[1] = NULL;
			argv[2] = NULL;
			execve("/bin/ls", argv, envp);
		}
	}
	if (ac == 3)
	{
		if (ft_strncmp(av[2], "-a", 2) == 0)
		{
			argv[0] = "ls";
			argv[1] = "-a";
			argv[2] = NULL;
			execve("/bin/ls", argv, envp);
		}
	}
	else
		printf("error\nmissing argument\n");
	return (0);
} */