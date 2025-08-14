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

void	err_n_exit(char *msg, t_pipex *pipex, int err_code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (pipex->pipe_fd[0] > -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] > -1)
		close(pipex->pipe_fd[1]);
	exit(err_code);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		err_n_exit("Correct syntax to run: ./pipex file1 cmd1 cmd2 file2\n",
			&pipex, 1);
	if (pipe(pipex.pipe_fd) == -1)
		err_n_exit("Pipe failed\n", &pipex, 1);
	pipex.infile = av[1];
	pipex.cmd1 = av[2];
	pipex.cmd2 = av[3];
	pipex.outfile = av[4];
	
}
