/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:22:29 by gita              #+#    #+#             */
/*   Updated: 2025/08/28 15:33:53 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

/**
Free a pointer then return NULL
 **/
char	*clean_wipe(void *trash)
{
	if (trash)
		free (trash);
	return (NULL);
}

/**
Write message to STDERR, close any fd > -1, free commands in struct, 
then exit with error code
 **/
void	close_free_n_exit(char *msg, t_straw *pipex, int err_code)
{
	if (msg)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);	
	}
	if (pipex->infile_fd > -1)
		close(pipex->infile_fd);
	if (pipex->outfile_fd > -1)
		close(pipex->outfile_fd);
	if (pipex->pipe_fd[0] > -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] > -1)
		close(pipex->pipe_fd[1]);
	if (pipex->cmd1)
		pipex->cmd1 = clean_wipe(pipex->cmd1);
	if (pipex->cmd2)
		pipex->cmd2 = clean_wipe(pipex->cmd2);
	exit(err_code);
}

/**
Free each element in the string array, free the double pointer itself,
then return NULL
 **/
char	*free_arr(char **arr)
{
	size_t	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			arr[i] = clean_wipe(arr[i]);
			i++;
		}
		arr = clean_wipe(arr);
	}
	return (NULL);
}

/**
Check why execve failed, free everything and exit accordingly
 **/
void	child_process_fail(int error_code, t_straw *ppx)
{
	if (error_code == ENOENT)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Command not found");
		close_free_n_exit(NULL, ppx, 127);
	}
	else if (error_code == EACCES || error_code == ENOEXEC)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Could not execute file");
		close_free_n_exit(NULL, ppx, 126);
	}
	else
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("execve");
		close_free_n_exit(NULL, ppx, EXIT_FAILURE);
	}
}
