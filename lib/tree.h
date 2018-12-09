//
// Created by Andrey Andriyaynen on 08/12/2018.
//

#ifndef AKINATOR_TREE_H
#define AKINATOR_TREE_H

//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//-----------------------------------------------------------------------------------------------------

typedef char* data_t;

struct node_t
{
	char * data;
	node_t * left;
	node_t * right;
};

struct tree_t
{
	node_t * root;
	int nVertex;
};

//-----------------------------------------------------------------------------------------------------

#ifndef CONSTS_H
#define CONSTS_H

enum CONSTS
{
	FOPEN_ERR = -1
};

#endif

enum TREE_CONSTS
{
	SRC_BUF_SIZE = 100
};
//-----------------------------------------------------------------------------------------------------

#define DOT_MAKE_PATH "dot -Tjpg -o /Users/andreyandriyaynen/CLionProjects/akinator/img/tree.jpg /Users/andreyandriyaynen/CLionProjects/akinator/img/tree.dot"
#define OPEN_IMG_PATH "open /Users/andreyandriyaynen/CLionProjects/akinator/img/tree.jpg"
#define DOT_PATH "/Users/andreyandriyaynen/CLionProjects/akinator/img/tree.dot"
#define SRC_PATH "/Users/andreyandriyaynen/CLionProjects/akinator/src/tree.txt"

//-----------------------------------------------------------------------------------------------------

int tree_ctor(tree_t * tree);
int tree_dtor(tree_t * tree);
int node_dtor(node_t * node);
int tree_dump(tree_t * tree);
int dot_write_node (node_t * node, FILE * fout);
int src_write_tree (tree_t * tree);
int src_write_node (node_t * node, FILE * fout);
node_t * node_ctor(char * node_data);
node_t * src_read_node(char ** src);
int skip_spaces(char ** text);
int tree_search( node_t * node );

//-----------------------------------------------------------------------------------------------------

#endif //AKINATOR_TREE_H
