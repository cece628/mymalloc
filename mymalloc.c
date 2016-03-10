/*use __FILE__,__LINE__ */
/*all: test0 test1 test2
test:test0.c...
gcc -o test0...

test1:test1.c..
gcc -o test1.c

extra credit: calloc, extra text cases
*/

#include <string.h>

#define memSize (5000) //whole memory size
#define blockSize (sizeof(struct blockMem)) //each block size
#define numOfBlock (memSize/blockSize)
#define malloc(x) mymalloc((x),__FILE__,__LINE__)//!!!!in .h file

//use link list to access each block of memory
struct blockMem{
  int size; //size of the block
  struct blockMem *next; //struct pointer within the block
  int ifFree; //int value to check if the block is freed. 1 for yes and 0 for no
};

void *head = numOfBlock;//head of the block, using linked list

//check if have free block to re-use free space
int freeBlock(){
  int i;
  for(i=0,i<numOfBlock,i++){
    if(head==NULL)
      return i; //return the index of the free block
  }
}

static int firstCall=0; //global int to check if the memory has been called. 1 for yes and 0 for no

void *mymalloc(unsigned int size, char *file, unsigned int line){
  if(size==0){
    printf("Fatal error in malloc call from line %d, in file %s\n", line, file);
    return -1;
  }


  if(firstCall=0){//fist call
    //use head for the beginning of the block
    //creat the whole block
    firstCall=1;
  }

  //now they have been initialized
  //do stuff

}

void *myfree(){

}
