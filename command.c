/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:26:13 by gita              #+#    #+#             */
/*   Updated: 2025/08/19 18:01:22 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

void	obey_command(t_straw *ppx, char *cmd, char **env)
{
	char	**command_chunks;

	if (!cmd || !*cmd)
		close_free_n_exit("Command not found\n", ppx, 127);
	if (!env)
		close_free_n_exit("No environment\n", ppx, EXIT_FAILURE);
	command_chunks = ft_split(cmd, ' ');
	if (!command_chunks || !command_chunks[0])
		close_free_n_exit("Split failed\n", ppx, EXIT_FAILURE);
	
}
