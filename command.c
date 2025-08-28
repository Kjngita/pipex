/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:26:13 by gita              #+#    #+#             */
/*   Updated: 2025/08/28 15:21:47 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

/**
Split the given command, find the full path to the command, run execve with
full path, splitted command args and environment
If execve has error, pass errno (global variable which gets a value when some
system function fails) to helper function to exit with correct exit code
 **/
void	obey_command(t_straw *ppx, char *cmd, char **env)
{
	char	**cmdv;
	char	*command_address;

	if (!cmd || !*cmd)
		close_free_n_exit("Command not found\n", ppx, 127);
	if (!env)
		close_free_n_exit("No environment\n", ppx, EXIT_FAILURE);
	cmdv = ft_split(cmd, ' ');
	if (!cmdv || !cmdv[0])
	{
		cmdv = free_arr(cmdv);
		close_free_n_exit("Split failed\n", ppx, EXIT_FAILURE);
	}
	command_address = locate_cmd(cmdv[0], env);
	execve(command_address, cmdv, env);
	cmdv = free_arr(cmdv);
	command_address = clean_wipe (command_address);
	child_process_fail(errno, ppx);
}

/**
- If command (without flags) has a "/", return that command if it's executable, 
NULL if not
- Find the PATH line in environment, return the path with the directory that
has the command (can be NULL)
 **/
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
	else
	{
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
	}
	return (correct_path(bunch_of_paths, cmd_main));
}

/**
Split the long environment PATH line into different directories separated
by ":", try pairing the directories with the command then return the path
that works (can be NULL)
 **/
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
		if (working_path != NULL)
			break ;
		i++;
	}
	env_paths = free_arr(env_paths);
	return (working_path);
}

/**
Adding a "/" to the end of directory name, then adding the command to the end
Return the command with the whole path if it's an executable file, NULL if not
 **/
char	*match_making(char *dir, char *cmd)
{
	char	*full_path;
	char	*whole_cmd;

	full_path = ft_strjoin(dir, '/');
	if (!full_path)
		return (NULL);
	whole_cmd = ft_strjoin(full_path, cmd);
	full_path = clean_wipe(full_path);
	if (!whole_cmd)
		return (NULL);
	if (access(whole_cmd, X_OK) == -1)
	{
		whole_cmd = clean_wipe(whole_cmd);
		return (NULL);
	}
	else if (access(whole_cmd, X_OK) == 0)
		return (whole_cmd);
}
