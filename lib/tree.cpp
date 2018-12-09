//
// Created by Andrey Andriyaynen on 08/12/2018.
//

#include "tree.h"

//-----------------------------------------------------------------------------------------------------

int tree_ctor(tree_t * tree)
{
	tree->root = nullptr;
	tree->nVertex = 0;
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int tree_dtor(tree_t * tree)
{
	if ( tree->root == nullptr )
	{
		tree->nVertex = 0;
		return 0;
	}
	
	if ( tree->root->left != nullptr )
		node_dtor( tree->root->left );
	
	if ( tree->root->right!= nullptr )
		node_dtor( tree->root->right );
	
	tree->nVertex = 0;
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int node_dtor(node_t * node)
{
	if ( node->left != nullptr )
		node_dtor( node->left );
	
	if ( node->right != nullptr )
		node_dtor( node->right );
	
	//free( node->data );
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int tree_dump(tree_t * tree)
{
	FILE * fout;
	
	if((fout = fopen(DOT_PATH, "w")) == nullptr)
		return FOPEN_ERR;
	
	fprintf(fout, "digraph\n"
		" {\n");
	
	if( tree->root != nullptr )
		dot_write_node( tree->root, fout );
	
	fprintf(fout, " }\n");
	
	fclose(fout);
	
	system(DOT_MAKE_PATH);
	system(OPEN_IMG_PATH);
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int dot_write_node (node_t * node, FILE * fout)
{
	if ( node->left != nullptr )
	{
		fprintf(fout, "    <%s> -> <%s>\n", node->data, node->left->data);
		dot_write_node(node->left, fout);
	}
	
	if( node->right != nullptr )
	{
		fprintf(fout, "    <%s> -> <%s>\n", node->data, node->right->data);
		dot_write_node(node->right, fout);
	}
	
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int src_write_tree (tree_t * tree)
{
	FILE * fout;
	
	if((fout = fopen(SRC_PATH, "w")) == nullptr)
		return FOPEN_ERR;
	
	if( tree->root != nullptr )
		src_write_node(tree->root, fout);
	
	fclose(fout);
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int src_write_node (node_t * node, FILE * fout)
{
	static int indent = -1;
	
	if( !node )
	{
		indent++;
		fprintf(fout, "%*s{}\n", indent * 4, "");
		indent--;
		return 0;
	}
	
	indent++;
	
	fprintf(fout, "%*s{", indent * 4, "");
	fprintf(fout, " %s\n", node->data);
	
	src_write_node(node->left, fout);
	src_write_node(node->right, fout);
	
	fprintf(fout, "%*s", indent * 4, "");
	fprintf(fout, "}\n");
	
	indent--;
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------

node_t * node_ctor(char * node_data)
{
	node_t * new_node = (node_t *) calloc(1, sizeof(node_t));
	
	new_node->data = strdup(node_data);
	new_node->left = nullptr;
	new_node->right = nullptr;
	
	return new_node;
}

//-----------------------------------------------------------------------------------------------------

node_t * src_read_node(char ** src)
{
	skip_spaces(src);
	
	char buf[50] = "";
	sscanf(*src, "%s", buf);
	(*src) += strlen(buf);
	
	if ( strcmp(buf, "{") != 0)
	{
		(*src)++;
		return nullptr;
	}
	
	int i = 0;
	skip_spaces(src);
	
	while (**src != '\n')
	{
		buf[i] = **src;
		i++;
		(*src)++;
	}
	
	(*src)++;
	
	printf("src read node: buf = %s\n", buf);
	
	node_t * n = node_ctor( buf );
	
	n->left = src_read_node( src );
	n->right = src_read_node( src );
	
	sscanf(*src, "%s", buf);
	skip_spaces(src);
	(*src) += strlen(buf);
	
	if ( strcmp(buf, "}") != 0 )
		return nullptr;
	
	(*src)++;
	
	return n;
}

//-----------------------------------------------------------------------------------------------------

int skip_spaces(char ** text)
{
	while (**text == ' ')
		(*text)++;
	
	return 0;
}