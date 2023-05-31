#include "../minishell.h"

int	my_env(t_data *data)
{
	int i = -1;
	while(data->envp[++i])
			printf("%s \n", data->envp[i]);
	return (-1);
}

int	my_cd(t_data *data)
{
	if (ft_strlen(data->line) > 3)
			return (chdir(data->line + 3));
		else
			return (chdir(getenv("HOME")));
}
