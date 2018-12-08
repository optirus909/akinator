#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------------------------------

typedef long data_t;

struct node_t
{
        data_t data;
        node_t * left;
        node_t * right;
};

struct tree_t
{
        node_t * root;
        int nVertex;
};

//-----------------------------------------------------------------------------------------------------

#define DOT_MAKE_PATH "dot -Tjpg -o /Users/andreyandriyaynen/CLionProjects/akinator/img/tree.jpg /Users/andreyandriyaynen/CLionProjects/akinator/img/tree.dot"
#define OPEN_IMG_PATH "open /Users/andreyandriyaynen/CLionProjects/akinator/img/tree.jpg"
#define DOT_PATH "/Users/andreyandriyaynen/CLionProjects/akinator/img/tree.dot"
#define SRC_PATH "/Users/andreyandriyaynen/CLionProjects/akinator/src/tree.txt"

enum CONSTS
{
        FOPEN_ERR = -1
};

//-----------------------------------------------------------------------------------------------------

int tree_ctor(tree_t * tree);
int tree_dtor(tree_t * tree);
int node_dtor(node_t * node);
int tree_dump(tree_t * tree);
int dot_write_node (node_t * node, FILE * fout);
int src_write_tree (tree_t * tree);
int src_write_node (node_t * node, FILE * fout);

//-----------------------------------------------------------------------------------------------------

int main()
{
        tree_t theTree;

        tree_ctor( &theTree );
	
	node_t root;
	root.left = nullptr;
	root.right = nullptr;
	root.data = 1;
	
	node_t child_left;
	child_left.data = 2;
	child_left.left = nullptr;
	child_left.right = nullptr;
	
	node_t child_right;
	child_right.data = 3;
	child_right.left = nullptr;
	child_right.right = nullptr;
	
	node_t kek;
	kek.data = 4;
	kek.left = nullptr;
	kek.right = nullptr;
	child_right.right = &kek;
	
	node_t kek2;
	kek2.data = 5;
	kek2.left = nullptr;
	kek2.right = nullptr;
	child_right.left = &kek2;
	
	root.left = &child_left;
	root.right = &child_right;
	theTree.root = &root;
	
	tree_dump( &theTree );
	tree_dump( &theTree );
	
	src_write_tree( &theTree );
	
	tree_dtor( &theTree );
	
	return 0;
}

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
		fprintf(fout, "    <%ld> -> <%ld>\n", node->data, node->left->data);
		dot_write_node(node->left, fout);
	}
	
	if( node->right != nullptr )
	{
		fprintf(fout, "    <%ld> -> <%ld>\n", node->data, node->right->data);
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
	fprintf(fout, "(%ld", node->data);
	
	if ( node->left != nullptr )
		src_write_node(node->left, fout);
	
	if( node->left == nullptr && node->right != nullptr )
		fprintf(fout, "()");
	
	if( node->right != nullptr )
		src_write_node(node->right, fout);
	
	if( node->left != nullptr && node->right == nullptr )
		fprintf(fout, "()");
	
	fprintf(fout, ")");
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int src_read_tree (tree_t * tree)
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

int src_read_node (node_t * node, FILE * fout)
{
	fprintf(fout, "(%ld", node->data);
	
	if ( node->left != nullptr )
		src_write_node(node->left, fout);
	
	if( node->left == nullptr && node->right != nullptr )
		fprintf(fout, "()");
	
	if( node->right != nullptr )
		src_write_node(node->right, fout);
	
	if( node->left != nullptr && node->right == nullptr )
		fprintf(fout, "()");
	
	fprintf(fout, ")");
	
	return 0;
}