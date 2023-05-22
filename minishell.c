/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:48:01 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/16 18:52:25 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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



int	is_builtins(char *line, t_data *data)
{
	if (!strncmp(line, "env", 3))
		return (my_env(data));
	if (!ft_strncmp(line, "cd", 2))
		return (my_cd(data));
	else
		return -1;
}

int	parsing (t_data *data, char *line)
{
	(void)data;
	int i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	prompt()
{
	int i;
	// char *str;
	char buf[100];

	getcwd(buf, sizeof(buf));
	i = ft_strlen(buf);
	buf[i] = '\0';
	printf("\033[0;32m\u2192\033[0m");
	printf("  ");
	while(buf[--i] != '/')
		;
	while(buf[i++])
		printf("\033[1;36m%c\033[0m", buf[i]);
	printf("\033[1;34m minishell: \033[0m");
}

// void	multiple_cmds(t_data *data, char *line)
// {
// 	int i;
// 	int	j;
// 	char **cmds;

// 	cmds = malloc(sizeof(char *) * data->cmds);
// 	i = 0;
// 	j = 0;
// 	while(line[i])
// 	{
// 		while(line[i] == ' ')
// 		{
// 			i++;
// 		}
// 		if (line[i] == '|')
// 		{
// 			while(line[i] != ' ')
// 			{
// 				cmds[j][i] = line[i];
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	j = -1;
// 	while(cmds[++j])
// 		process(cmds[j], data);
// }


void	exec_process1(t_data *data, char *str, char **envp)
{
	char	**mycmdargs;
	char	*path;

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
	execve(path, mycmdargs, envp);
	ft_freetab(mycmdargs);
	free(data->pid);
	exit(1);
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
		// close_fd(&data->pipes[1]);
		close_fd(&data->pipes[0]);
	}
	else
		second_part_dupnclose(i, data);
}

void	process(t_data *data)
{
	int	i;
	// int	j;
	char **cmds;
	// int d;

	// d = 0;
	cmds = ft_split(data->line, '|');
	// i = 0;
	// j = 0;
	// while(data->line[i])
	// {
	// 	while(data->line[i] == ' ')
	// 	{
	// 		i++;
	// 	}
	// 	if (data->line[i] == '|')
	// 	{
	// 		i++;
	// 		while(data->line[i] == ' ')
	// 		{
	// 			i++;
	// 		}
	// 		while(data->line[i] != ' ')
	// 		{
	// 			cmds[j][d] = data->line[i];
	// 			d++;
	// 			i++;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// j = -1;
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
			exec_process1(data, cmds[i], data->envp);
		}
		close_fd(&data->pipes[1]);
		data->prev = data->pipes[0];
		// close_fd(&data->pipes[0]);
		// if (i == 0 && data->is_here_doc == 1)
		// 	close_fd(&data->here_doc[0]);
		i++;
	}
	i = -1;
	while (++i < data->cmds)
		waitpid(data->pid[i], NULL, 0);
	i = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char buf[100];
	int	i;
	// int	hist;

	i = 0;
	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	data.cmds = 0;
	data.prev = -1;
	data.envp = envp;
	data.pid = malloc(sizeof(int) * data.cmds);
	data.historic = malloc(sizeof(char *) * 10);
	prompt();
	printf("%d", data.cmds);
	while(1)
	{
		data.line = readline(buf);
		add_history(data.line);
		data.cmds = word_count(data.line, '|');
		printf("nmbre de cmds >> %d ", data.cmds);
		data.historic[i] = data.line;
		if (!strncmp(data.line, "exit", 5))
		{
			return (0);
		}
		if (check_line(data.line) == 1)
			printf("Error check_line.\n");
		else if (data.line[0] != '\0' && is_builtins(data.line, &data) == -1)
		{
			if (data.cmds > 1)
				process(&data);
			else
				exec_process(&data, data.line);
		}
		printf("cmd >> %s", data.historic[i]);
		i++;
		prompt();
	}
	return (0);
}
