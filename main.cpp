#include <stdio.h>
#include <stdlib.h>
#include "lib/tree.h"

//-----------------------------------------------------------------------------------------------------

#ifndef CONSTS_H
#define CONSTS_H

enum CONSTS
{
	FOPEN_ERR = -1
};

#endif

//-----------------------------------------------------------------------------------------------------

char * text_reading(FILE *file, long * FileSize);

//-----------------------------------------------------------------------------------------------------

int main()
{
	FILE *fin;
	
	if((fin = fopen(SRC_PATH, "r")) == nullptr)
		return FOPEN_ERR;
	long  filesize;
	char * src = text_reading(fin, &filesize);
	fclose(fin);
	
        tree_t theTree;

        tree_ctor( &theTree );
	
	theTree.root = src_read_node( &src );
	
	tree_dump( &theTree );
	
	//src_write_tree( &theTree );
	
	tree_dtor( &theTree );
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------

char * text_reading(FILE *file, long * FileSize)
{
	fseek(file, 0, SEEK_END);
	*FileSize = ftell(file);
	rewind(file);
	char * buffer = (char *) calloc(*FileSize, sizeof(char));
	fread(buffer, sizeof(char *), *FileSize, file);
	
	return buffer;
}