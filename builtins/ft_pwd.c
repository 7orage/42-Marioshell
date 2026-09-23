#include "minishell.h"

/*
ft_pwd	-> PRINT THE WORKING DIRECTORY
*/

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (err_cmd("pwd", strerror(errno), 1));
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
