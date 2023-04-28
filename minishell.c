/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:48:01 by slevaslo          #+#    #+#             */
/*   Updated: 2023/04/13 17:15:40 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	word_count(char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			j++;
		i++;
	}
	return (i);
}

void	exec_process(t_data *data, char *str)
{
	char	**mycmdargs;
	char	*path;
	pid_t	pid_child;

	mycmdargs = ft_split(str, ' ');
	if (!mycmdargs)
		return (ft_freetab(mycmdargs));
	if (!mycmdargs[0])
	{
		free(data->pid);
		not_find(mycmdargs);
	}
	path = find_path(mycmdargs[0], data);
	if (!path)
	{
		free(data->pid);
		not_find(mycmdargs);
	}
	pid_child = fork();
	if (pid_child == 0)
	{
		execve(path, mycmdargs, data->envp);
		ft_freetab(mycmdargs);
		free(data->pid);
	}
	waitpid(pid_child, NULL, 0);
}

void	dupncloses(int i, t_data *data)
{
	if (i == 0)
	{
		// if (data->fd_in == -1)
		// {
		// 	close_fd(&data->pipes[0]);
		// 	close_fd(&data->pipes[1]);
		// 	close_fd(&data->here_doc[0]);
		// 	error(data);
		// }
		dup2(data->pipes[1], STDOUT_FILENO);
		close_fd(&data->pipes[1]);
		close_fd(&data->pipes[0]);
	}
	else
		second_part_dupnclose(i, data);
}

void	process(char *prompt, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmds)
	{
		if (i != data->cmds - 1)
			pipe(data->pipes);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			error(data);
		else if (data->pid[i] == 0)
		{
			dupncloses(i, data);
			exec_process(data, prompt);
		}
		close_fd(&data->pipes[1]);
		close_fd(&data->prev);
		data->prev = data->pipes[0];
		if (i == 0 && data->is_here_doc == 1)
			close_fd(&data->here_doc[0]);
		i++;
	}
	i = -1;
	while (++i < data->cmds)
		waitpid(data->pid[i], NULL, 0);
}

void	builtins(char *line, t_data *data)
{
	if (!strncmp(line, "env", 3))
		while(*data->envp++)
			printf("%s", *data->envp);
	else
		return ;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char buf[100];
	char *line;
	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	data.prev = -1;
	data.envp = envp;
	printf("%s : ", getenv("PWD"));

	while(1)
	{
		line = readline(buf);
		if (!strncmp(line, "exit", 5))
			break ;
		// builtins(line, &data);
		if (check_line(line) == 1)
			printf("Error check_line.\n");
		else if (line != NULL)
		{
			printf("%s : ", getenv("PWD"));
			exec_process(&data, line);
		// process(line, &data);
		}
	}
	return (0);
}
