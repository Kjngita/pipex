/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:26:13 by gita              #+#    #+#             */
/*   Updated: 2025/09/03 23:22:04 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pipex.h"

/*
- Split the given command, find the full path to the command, run execve with
(full path, splitted command args, environment)
- If execve has error, pass errno (global variable which gets a value when some
system function fails) to helper function to exit with correct exit code
 */
void	obey_command(t_straw *ppx, char *cmd, char **env)
{
	char	**cmdv;
	char	*command_address;

	if (!cmd || !*cmd)
		close_fds_n_exit("No command\n", ppx, 127);
	if (!env)
		close_fds_n_exit("No environment\n", ppx, EXIT_FAILURE);
	cmdv = ft_split(cmd, ' ');
	if (!cmdv || !cmdv[0])
	{
		cmdv = free_arr(cmdv);
		close_fds_n_exit("Split failed\n", ppx, EXIT_FAILURE);
	}
	command_address = locate_cmd(cmdv[0], env);
	if (!command_address)
	{
		cmdv = free_arr(cmdv);
		perror("pipex: Command not found");
		close_fds_n_exit(NULL, ppx, 127);
	}
	execve(command_address, cmdv, env);
	cmdv = free_arr(cmdv);
	command_address = clean_wipe (command_address);
	child_process_fail(errno, ppx);
}

/*
- If command (without flags) has a "/", return a duplicate of that command
- Find the PATH line in environment, return the path with the directory that
has the command (can be NULL)
 */
char	*locate_cmd(char *cmd_main, char **env)
{
	size_t	i;
	char	*bunch_of_paths;

	bunch_of_paths = NULL;
	if (ft_strchr(cmd_main, '/'))
		return (ft_strdup(cmd_main));
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

/*
- Split the long environment PATH line by ":" into different directories
- Try pairing the directories with the command
- Return the path that exists (can be NULL)
 */
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

/*
- Add a "/" to the end of directory name, then add the command to the end
- Return the command with the whole path if the file exists, NULL if not
 */
char	*match_making(char *dir, char *cmd)
{
	char	*full_path;
	char	*whole_cmd;

	full_path = ft_strjoin(dir, "/");
	if (!full_path)
		return (NULL);
	whole_cmd = ft_strjoin(full_path, cmd);
	full_path = clean_wipe(full_path);
	if (!whole_cmd)
		return (NULL);
	if (access(whole_cmd, F_OK) == -1)
	{
		whole_cmd = clean_wipe(whole_cmd);
		return (NULL);
	}
	return (whole_cmd);
}

/*
Check why execve failed with errno and exit with according exit code
 */
void	child_process_fail(int error_code, t_straw *ppx)
{
	if (error_code == ENOENT)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Command nonexistent");
		close_fds_n_exit(NULL, ppx, 127);
	}
	else if (error_code == EACCES || error_code == ENOEXEC)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Could not execute file");
		close_fds_n_exit(NULL, ppx, 126);
	}
	else
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror("Failed execve");
		close_fds_n_exit(NULL, ppx, EXIT_FAILURE);
	}
}
