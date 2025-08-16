/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_pipex.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:57:10 by gita              #+#    #+#             */
/*   Updated: 2025/08/14 23:01:54 by gita             ###   ########.fr       */
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
}	t_straw;


#endif