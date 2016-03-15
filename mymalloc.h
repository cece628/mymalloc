#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdlib.h>
#include <stdio.h>
#define malloc(x) mymalloc((x),__FILE__,__LINE__)//!!!!in .h file

typedef struct blockMem blockMem;

//use link list to access each block of memory
struct blockMem{
  int size; //size of the block
  struct blockMem *next, *prev; //struct pointer within the block
  int ifFree; //int value to check if the block is freed. 1 for yes and 0 for no
};

void *mymalloc(unsigned int size, char *file, unsigned int line);
void myfree(void *p, char *file, int line);
int freeBlock(blockMem *ptr);
//void *mycalloc(int ct, unsigned int size, char *file, int line);
//void *myrealloc(void *p, unsigned int size, char *file, int line);
size_t getSize(void * p);

#endif
