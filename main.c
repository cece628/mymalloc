#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.c"

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define calloc( x , y ) mycalloc( x, y, __FILE__, __LINE__ )
#define realloc( x , y ) myrealloc( x, y, __FILE__, __LINE__ )

struct node { 
	struct node *next;
	int data;
};

int main(int argc, char** argv) {

	// Test Case 1 - free()ing pointers that were never allocated
	int x;
	free(&x);



	return 0;
}
