#include "minishell.h"

/*
expand_line	-> EXPAND ONE HEREDOC LINE, OR COPY IT AS IS IF env IS NULL
write_hd	-> READ LINES UNTIL THE DELIMITER AND WRITE THEM IN THE FILE
make_hd		-> BUILD ONE HEREDOC, KEEP ITS FD, UNLINK THE TEMP FILE AT ONCE
walk_hd		-> WALK THE AST LEFT FIRST, SO HEREDOCS ARE READ IN ORDER
collect_heredocs -> READ EVERY HEREDOC OF THE LINE BEFORE ANYTHING RUNS
*/

static char	*expand_line(char *line, t_env *env)
{
	char	buf[BUF_MAX];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && j < BUF_MAX - 1)
	{
		if (line[i] == '$' && env)
			i += expand(&line[i], buf, &j, env);
		else
		{
			buf[j] = line[i];
			i++;
			j++;
		}
	}
	buf[j] = '\0';
	return (ft_strdup(buf));
}

static int	write_hd(int fd, char *delim, int quoted, t_env *env)
{
	char	*line;
	char	*out;

	if (quoted)
		env = NULL;
	line = readline("> ");
	while (line && ft_strncmp(line, delim, ft_strlen(delim) + 1))
	{
		out = expand_line(line, env);
		free(line);
		if (!out)
			return (0);
		ft_putendl_fd(out, fd);
		free(out);
		line = readline("> ");
	}
	free(line);
	if (g_signal == SIGINT)
		return (0);
	return (1);
}

static int	make_hd(t_lst_ast *node, t_env *env)
{
	int	fd;

	if (!node->red_file)
		return (0);
	fd = open(HD_TMP, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (err_file(HD_TMP));
	if (!write_hd(fd, node->red_file, node->hd_quoted, env))
		return (close(fd), unlink(HD_TMP), 0);
	close(fd);
	node->hd_fd = open(HD_TMP, O_RDONLY);
	unlink(HD_TMP);
	if (node->hd_fd < 0)
		return (err_file(HD_TMP));
	return (1);
}

static int	walk_hd(t_lst_ast *node, t_env *env)
{
	if (!node)
		return (1);
	if (!walk_hd(node->left, env))
		return (0);
	if (!walk_hd(node->right, env))
		return (0);
	if (node->node_type == N_RED && node->token_type == TOK_RED_BLS)
		return (make_hd(node, env));
	return (1);
}

int	collect_heredocs(t_lst_ast *ast, t_env *env)
{
	int	save;
	int	ok;

	save = dup(STDIN_FILENO);
	if (save < 0)
	{
		err_sys("dup");
		return (0);
	}
	sig_heredoc();
	ok = walk_hd(ast, env);
	if (g_signal == SIGINT)
		dup2(save, STDIN_FILENO);
	close(save);
	sig_prompt();
	return (ok);
}
