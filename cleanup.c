/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:22:29 by gita              #+#    #+#             */
/*   Updated: 2025/09/03 23:34:55 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

/*
Write message if any to STDERR, close any fd > -1, then exit with error code
 */
void	close_fds_n_exit(char *msg, t_straw *pipex, int err_code)
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
	exit(err_code);
}

/*
Free a pointer then return NULL
 */
void	*clean_wipe(void *trash)
{
	if (trash)
		free (trash);
	return (NULL);
}

/*
Free each element in the string array, free the double pointer itself,
then return NULL
 */
char	**free_arr(char **arr)
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
