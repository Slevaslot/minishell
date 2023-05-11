/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:48:01 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/11 19:33:28 by slevaslo         ###   ########.fr       */
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

int	builtins(char *line, t_data *data)
{
	if (!strncmp(line, "env", 3))
		while(*data->envp++)
				return (printf("%s \n", *data->envp)); // probleme ici
	if (!ft_strncmp(line, "cd", 2))
	{
		if (ft_strlen(line) > 3)
			return (chdir(line + 3));
		else
			return (chdir(getenv("HOME")));
	}
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
	char *str;

	str = getenv("PWD");
	i = ft_strlen(str);
	str[i] = '\0';
	printf("\x1b[32m->\x1b[0m ");
	while(str[--i] != '/')
		;
	while(str[i++])
		printf("%c", str[i]);
	printf(" : ");
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char buf[1000];
	char *line;
	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	data.prev = -1;
	data.envp = envp;
	prompt();
	while(1)
	{
		line = readline(buf);
		if (line == NULL)
			break ;
		if (!strncmp(line, "exit", 5))
			break ;
		// if (builtins(line, &data) != -1 )
		// 	printf("builtused");
		if (check_line(line) == 1)
			printf("Error check_line.\n");
		else if (line != NULL && builtins(line, &data) == -1)
		{
			// if (parsing(&data, line) == 0)
			exec_process(&data, line);
			// else
			// process(line, &data);
		}
		prompt();
	}
	return (0);
}
