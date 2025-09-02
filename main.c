/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:56:31 by gita              #+#    #+#             */
/*   Updated: 2025/09/02 15:53:19 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

/*
- Check argument count
- Create a pipe, spawn 2 child processes with helper function, then close pipe
- Wait for child 1 to finish, wait for child 2 to finish and get child 2's exit status
- If child 2 exited normally, return the exit code. If not, return exit failure to parent
 */
int	main(int ac, char **av, char **envp)
{
	t_straw	ppx;
	int		exit_status;

	if (ac != 5)
		close_free_n_exit("Correct usage: ./pipex file1 cmd1 cmd2 file2\n",
			&ppx, EXIT_FAILURE);
	if (pipe(ppx.pipe_fd) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Pipe failed");
		close_free_n_exit(NULL, &ppx, EXIT_FAILURE);
	}
	ppx.cmd1 = av[2];
	ppx.cmd2 = av[3];
	make_children(&ppx, av[1], av[4], envp);
	close(ppx.pipe_fd[0]);
	close(ppx.pipe_fd[1]);
	waitpid(ppx.child_1, &exit_status, 0);
	waitpid(ppx.child_2, &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}

/*
Fork 2 child processes, open files and redirect accordingly, each child process
handles their own command
 */
void	make_children(t_straw *ppx, char *in_name, char *out_name, char **envp)
{
	ppx->child_1 = fork();
	if (ppx->child_1 == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Forking 1st child unsuccessful");
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
		perror("Forking 2nd child unsuccessful");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (ppx->child_2 == 0)
	{
		create_outfile_n_redirect(ppx, out_name);
		obey_command(ppx, ppx->cmd2, envp);
	}
}

/*
- Close pipe_read since pipe doesn't need to read itself
- Open infile, redirect infile as the stdin of command 
- Close infile since command stdin got the info
- Redirect stdout of command to pipe_write (write to pipe)
- Close pipe_write, let command do the work
 */
void	open_infile_n_redirect(t_straw *ppx, char *filename)
{
	close(ppx->pipe_fd[0]);
	ppx->infile_fd = open(filename, O_RDONLY);
	if (ppx->infile_fd < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Opening infile failed");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	if (dup2(ppx->infile_fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Redirecting infile->cmdread failed");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->infile_fd);
	if (dup2(ppx->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Redirecting cmdwrite->pipe failed");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->pipe_fd[1]);
}

/*
- Close pipe_write since pipe doesn't need to write anywhere
- Redirect pipe_read as the stdin of command
- Close pipe_read since command stdin got the info
- Open/Create outfile, redirect stdout of command to outfile (write to outfile)
- Close outfile, let command do the work
 */
void	create_outfile_n_redirect(t_straw *ppx, char *filename)
{
	close(ppx->pipe_fd[1]);
	if (dup2(ppx->pipe_fd[0], STDIN_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Redirecting pipe->cmdread failed");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	ppx->outfile_fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (ppx->outfile_fd < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Outfile failed");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->pipe_fd[0]);
	if (dup2(ppx->outfile_fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Redirecting cmdwrite->outfile failed");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
	close(ppx->outfile_fd);
}

