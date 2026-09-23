#include "minishell.h"

/*
wait_status	-> WAIT FOR A CHILD AND TRANSLATE ITS EXIT CODE
set_status	-> WRITE THE EXIT CODE IN THE HIDDEN "?" VARIABLE
*/

int	wait_status(pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	set_status(t_env *env, int code)
{
	char	*value;

	value = ft_itoa(code);
	if (!value)
		return ;
	while (env)
	{
		if (env->name && env->name[0] == '?' && env->name[1] == '\0')
		{
			free(env->content);
			env->content = value;
			return ;
		}
		env = env->next;
	}
	free(value);
}
