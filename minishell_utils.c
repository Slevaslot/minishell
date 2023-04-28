/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:38:08 by slevaslo          #+#    #+#             */
/*   Updated: 2023/04/13 17:13:30 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int *fd)
{
	if (*fd < 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	second_part_dupnclose(int i, t_data *data)
{
	if (i == data->cmds)
	{
		// data->fd_out = open(data->fd_ch, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// if (data->fd_out == -1)
		// {
		// 	close_fd(&data->prev);
		// 	error(data);
		// }
		dup2(data->prev, STDIN_FILENO);
		close_fd(&data->prev);
		dup2(data->fd_out, STDOUT_FILENO);
		close_fd(&data->fd_out);
	}
	else
	{
		close_fd(&data->pipes[0]);
		dup2(data->prev, STDIN_FILENO);
		close_fd(&data->prev);
		dup2(data->pipes[1], STDOUT_FILENO);
		close_fd(&data->pipes[1]);
	}
}

void	ft_freetab(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*path_is_ok(char **paths, char *cmd)
{
	char	*fpath;
	char	*part_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			return (free(part_path), NULL);
		fpath = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!fpath)
			return (free(fpath), NULL);
		if (access(fpath, F_OK | X_OK) == 0)
			return (fpath);
		free(fpath);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_data *data)
{
	char	**paths;
	char	*str;
	char *envp;

	(void) data;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	envp = getenv("PATH");
	paths = ft_split(envp + 5, ':');
	if (!paths)
		return (ft_freetab(paths), NULL);
	str = path_is_ok(paths, cmd);
	ft_freetab(paths);
	if (!str)
		return (free(str), NULL);
	return (str);
}

void	error(t_data *data)
{
	(void)data;
	free(data->pid);
	perror("\033[31;5merror\033[0m ");
	exit(EXIT_FAILURE);
}

void	not_find(char **mycmdargs)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	if (mycmdargs[0])
	{
		ft_putstr_fd(mycmdargs[0], 2);
	}
	ft_freetab(mycmdargs);
	ft_putstr_fd("\n", 2);
	// exit(EXIT_FAILURE);
}
