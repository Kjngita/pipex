/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:56:31 by gita              #+#    #+#             */
/*   Updated: 2025/08/16 22:16:52 by gita             ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_straw	ppx;

	if (ac != 5)
		close_free_n_exit("Correct syntax to run: ./pipex file1 cmd1 cmd2 file2\n",
			&ppx, EXIT_FAILURE);
	if (pipe(ppx.pipe_fd) == -1)
		close_free_n_exit("Pipe failed\n", &ppx, EXIT_FAILURE);
	ppx.cmd1 = av[2];
	ppx.cmd2 = av[3];
	make_children(&ppx, av[1], av[4], envp);

	close(ppx.pipe_fd[0]);
	close(ppx.pipe_fd[1]);
	
}

void	make_children(t_straw *ppx, char *infile_name, char *outfile_name, char **envp)
{
	pid_t	child_1;
	pid_t	child_2;

	child_1 = fork();
	child_2 = fork();
	if (child_1 == -1 || child_2 == -1)
	{
		perror("Child stillbirth\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (child_1 == 0)
	{
		open_infile_n_redirect(ppx, infile_name);
		//obey_command(int child, envp);
	}
	if (child_2 == 0)
	{
		create_outfile_n_redirect(ppx, outfile_name);
		//obey_command
	}
	
	
}	

void	open_infile_n_redirect(t_straw *ppx, char *filename)
{
	close(ppx->pipe_fd[0]);
	ppx->infile_fd = open(filename, O_RDONLY);
	if (ppx->infile_fd < 0)
	{
		perror("Opening infile failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (dup2(ppx->infile_fd, STDIN_FILENO) == -1)
	{
		perror("Redirecting infile->cmdread failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->infile_fd);
	if (dup2(ppx->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("Redirecting cmdwrite->pipe failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->pipe_fd[1]);
}

void	create_outfile_n_redirect(t_straw *ppx, char *filename)
{
	close(ppx->pipe_fd[1]);
	ppx->outfile_fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (ppx->outfile_fd < 0)
	{
		perror("Outfile failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (dup2(ppx->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("Redirecting pipe->cmdread failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->pipe_fd[0]);
	if (dup2(ppx->outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("Redirecting cmdwrite->outfile failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->outfile_fd);
}

