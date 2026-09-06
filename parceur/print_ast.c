#include "parceur.h"

static const char *node_type_str(t_node_type type)
{
	if (type == N_RED)  return "N_RED";
	if (type == N_PIPE) return "N_PIPE";
	if (type == N_CMD)  return "N_CMD";
	return "TOK_EOF";
}

static void print_ast_rec(t_lst_ast *node, int depth, int is_right)
{
	int i;

	if (!node)
		return ;
	i = 0;
	while (i < depth - 1)
	{
		printf("│   ");
		i++;
	}
	if (depth > 0)
	{
		if (is_right)
			printf("├── ");
		else
			printf("└── ");
	}
	printf("[%s]", node_type_str(node->node_type));
	if (node->node_type == N_CMD && node->tokens)
	{
		int j = 0;
		printf(" |");
		while (node->tokens[j])
		{
			printf(" %s", node->tokens[j]);
			j++;
		}
		printf(" |");
	}
	if (node->red_file)
		printf(" -> \"%s\"", node->red_file);
	printf("\n");
	if (node->left || node->right)
	{
		print_ast_rec(node->right, depth + 1, 1);
		print_ast_rec(node->left,  depth + 1, 0);
	}
}

void    print_ast(t_lst_ast *root)
{
	if (!root)
	{
		printf("(empty AST)\n");
		return ;
	}
	printf("AST:\n");
	print_ast_rec(root, 0, 0);
}