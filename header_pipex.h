/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_pipex.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:57:10 by gita              #+#    #+#             */
/*   Updated: 2025/08/26 23:19:48 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_PIPEX_H
# define HEADER_PIPEX_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct s_straw
{
	char	*cmd1;
	char	*cmd2;
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	pid_t	child_1;
	pid_t	child_2;
}	t_straw;

char	*clean_wipe(void *trash);
void	close_free_n_exit(char *msg, t_straw *pipex, int err_code);
void	free_arr(char **arr);

void	make_children(t_straw *ppx, char *in_name, char *out_name, char **envp);
void	open_infile_n_redirect(t_straw *ppx, char *filename);
void	create_outfile_n_redirect(t_straw *ppx, char *filename);

void	obey_command(t_straw *ppx, char *cmd, char **env);
char	*locate_cmd(char *cmd_main, char **env);

#endif