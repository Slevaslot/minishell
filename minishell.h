/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:47:35 by slevaslo          #+#    #+#             */
/*   Updated: 2023/04/13 17:15:26 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <signal.h>

typedef struct data
{
	int		prev;
	int		cmds;
	int		fd_out;
	int		fd_in;
	int		here_doc[2];
	int		pipes[2];
	int		is_here_doc;
	int		*pid;
	char	*fd_ch;
	char	*fd_in_ch;
	char **envp;
	char	*line;
	char **historic;
}t_data;

void	exec_process(t_data *data, char *str);
void	not_find(char **mycmdargs);
void	error(t_data *data);
void	ft_freetab(char **str);
char	*find_path(char *cmd, t_data *data);
char	*path_is_ok(char **paths, char *cmd);
void	process(t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);
void	here_doc(char *argv, t_data *data);
void	second_part_dupnclose(int i, t_data *data);
void	close_fd(int *fd);
int check_line(char *line);
int		word_count(char *s, char c);
//builtins
int	my_env(t_data *data);
int	my_cd(t_data *data);

#endif
