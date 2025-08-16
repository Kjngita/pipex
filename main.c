/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:56:31 by gita              #+#    #+#             */
/*   Updated: 2025/08/14 23:09:36 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

void	close_free_n_exit(char *msg, t_straw *pipex, int err_code)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	if (pipex->infile_fd > -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd > -1)
		close(pipex->outfile_fd);
	if (pipex->pipe_fd[0] > -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] > -1)
		close(pipex->pipe_fd[1]);
	if (pipex->cmd1)
	{
		free(pipex->cmd1);
		pipex->cmd1 = NULL;
	}
	if (pipex->cmd2)
	{
		free(pipex->cmd2);
		pipex->cmd2 = NULL;
	}
	exit(err_code);
}

void	open_infile_n_redirect(t_straw *pipe, char *filename)
{
	pipe->infile_fd = open(filename, O_RDONLY);
	if (pipe->infile_fd < 0)
	{
		perror("Opening infile failed\n");
		close_free_n_exit(NULL, pipe, EXIT_FAILURE);
	}
	if (dup2(pipe->infile_fd, STDIN_FILENO) == -1)
	{
		perror("Redirecting infile-read failed\n");
		close_free_n_exit(NULL, pipe, EXIT_FAILURE);
	}
	close(pipe->infile_fd);
	if (dup2(pipe->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("Redirecting pipe-write failed\n");
		close_free_n_exit(NULL, pipe, EXIT_FAILURE);
	}
	close(pipe->pipe_fd[0]);
}
	// if (position == 4)
	// {
	// 	pipe->outfile_fd = open(filename, O_WRONLY | O_CREAT, 0644);
	// 	if (pipe->outfile_fd < 0)
	// 	{
	// 		perror("Outfile failed\n");
	// 		close_free_n_exit(NULL, pipe, EXIT_FAILURE);
	// 	}
	// }

int	main(int ac, char **av, char **envp)
{
	t_straw	pipex;

	if (ac != 5)
		close_free_n_exit("Correct syntax to run: ./pipex file1 cmd1 cmd2 file2\n",
			&pipex, EXIT_FAILURE);
	if (pipe(pipex.pipe_fd) == -1)
		close_free_n_exit("Pipe failed\n", &pipex, EXIT_FAILURE);
	pipex.cmd1 = av[2];
	pipex.cmd2 = av[3];
	open_infile_n_redirect(&pipex, av[1]);
	// open_files_n_redirect(&pipex, av[4]);
}
