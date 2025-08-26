/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:26:13 by gita              #+#    #+#             */
/*   Updated: 2025/08/26 23:16:20 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

void	obey_command(t_straw *ppx, char *cmd, char **env)
{
	char	**command_chunks;
	char	*command_address;

	if (!cmd || !*cmd)
		close_free_n_exit("Command not found\n", ppx, 127);
	if (!env)
		close_free_n_exit("No environment\n", ppx, EXIT_FAILURE);
	command_chunks = ft_split(cmd, ' ');
	if (!command_chunks || !command_chunks[0])
	{
		free_arr(command_chunks);
		close_free_n_exit("Split failed\n", ppx, EXIT_FAILURE);
	}
	command_address = locate_cmd(command_chunks[0], env);
	if (!command_address)
	{
		free_arr(command_chunks);
		close_free_n_exit("Command not found\n", ppx, 127);
	}
	execve(command_address, command_chunks, env);
	
}

char	*locate_cmd(char *cmd_main, char **env)
{
	char	*cmd_path;
	size_t	i;
	char	*bunch_of_paths;

	if (ft_strchr(cmd_main, '/'))
	{
		if (access(cmd_main, X_OK) == -1)
			return (NULL);
		else if (access(cmd_main, X_OK) == 0)
			return (cmd_main);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			bunch_of_paths = env[i] + 5;
			break ;
		}
		i++;
	}
	cmd_path = correct_path(bunch_of_paths, cmd_main);
	return (cmd_path);
}

char	*correct_path(char *paths_in_1_line, char *cmd)
{
	char	**env_paths;
	char	*working_path;
	size_t	i;

	env_paths = ft_split(paths_in_1_line, ':');
	if (!env_paths || !env_paths[0])
		return (NULL);
	i = 0;
	while (env_paths[i])
	{
		working_path = match_making(env_paths[i], cmd);
		i++;
	}
	
}

char	*match_making(char *dir, char *cmd)
{
	char	*full_path;
	char	*test;

	full_path = ft_strjoin(dir, '/');
	if (!full_path)
		return (NULL);
	test = ft_strjoin(full_path, cmd);
	if (!test)
	{
		free (full_path);
		
	}
}
