/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:56:31 by gita              #+#    #+#             */
/*   Updated: 2025/08/26 23:20:12 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_straw	ppx;

	if (ac != 5)
		close_free_n_exit("Correct usage: ./pipex file1 cmd1 cmd2 file2\n",
			&ppx, EXIT_FAILURE);
	if (pipe(ppx.pipe_fd) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Pipe failed\n");
		close_free_n_exit(NULL, &ppx, EXIT_FAILURE);
	}
	ppx.cmd1 = av[2];
	ppx.cmd2 = av[3];
	make_children(&ppx, av[1], av[4], envp);
	close(ppx.pipe_fd[0]);
	close(ppx.pipe_fd[1]);

}

void	make_children(t_straw *ppx, char *in_name, char *out_name, char **envp)
{
	ppx->child_1 = fork();
	if (ppx->child_1 == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Forking 1st child unsuccessful\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (ppx->child_1 == 0)
	{
		open_infile_n_redirect(ppx, in_name);
		obey_command(ppx, ppx->cmd1, envp);
	}
	ppx->child_2 = fork();
	if (ppx->child_2 == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Forking 2nd child unsuccessful\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (ppx->child_2 == 0)
	{
		create_outfile_n_redirect(ppx, out_name);
		obey_command(ppx, ppx->cmd2, envp);
	}
}	

void	open_infile_n_redirect(t_straw *ppx, char *filename)
{
	close(ppx->pipe_fd[0]);
	ppx->infile_fd = open(filename, O_RDONLY);
	if (ppx->infile_fd < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Opening infile failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (dup2(ppx->infile_fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Redirecting infile->cmdread failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->infile_fd);
	if (dup2(ppx->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
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
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Outfile failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (dup2(ppx->pipe_fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Redirecting pipe->cmdread failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->pipe_fd[0]);
	if (dup2(ppx->outfile_fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Redirecting cmdwrite->outfile failed\n");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->outfile_fd);
}
