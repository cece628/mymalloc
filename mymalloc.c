/*use __FILE__,__LINE__ */
/*all: test0 test1 test2
test:test0.c...
gcc -o test0...

test1:test1.c..
gcc -o test1.c

extra credit: calloc, extra text cases
*/

#include <string.h>
#include "mymalloc.h" 
#define memSize 5000 //whole memory size
#define blockSize (sizeof(struct blockMem)) //each block size
#define numOfBlock (memSize/blockSize)


static void *blockInd[memSize/blockSize];

/*//use link list to access each block of memory, move to .h file
struct blockMem{
  int size; //size of the block
  struct blockMem *next; //struct pointer within the block
  int ifFree; //int value to check if the block is freed. 1 for yes and 0 for no
};
*/

static int i=0;

//check if have free block to re-use free space
int freeBlock(blockMem *ptr){
  int ifFree = 0; //not free at first
  for(i=0;i< (numOfBlock);i++){
    if(ptr == blockInd[i] && !ptr->ifFree){
	ifFree = 1;//already free
      	return 1; 
	}
  }
  return 0;//no freeBlock
}

//get the index of the free block
static int getFree(){
	int i;
	for(i=0; i< (numOfBlock);i++){
		if(blockInd[i] == 0)
			return i;
	}
	return 1;
}



void *mymalloc(unsigned int size, char *file, unsigned int line){

  struct blockMem *next, *new;
  static int firstCall=0; //global int to check if the memory has been called. 1 for yes and 0 for no
  static struct blockMem *head, *tail;
  if(size==0){
    printf("Fatal error in malloc call from line %d, in file %s\n", line, file);
    return -1;
  }


  if(firstCall=0){//fist call
    //use head for the beginning of the block
    //creat the whole block
    head->next=0;
    head->size=5000-blockSize;
    firstCall=1;
    head->ifFree=0;
  }

  //now they have been initialized
  //do stuff

  new = head;
  do{
    if(new->size < size|| !new->ifFree){//not enough memory size or not freed , move to next
      new = new->next;
    }else if(new->size < (size + blockSize) ){//enough memory, return the head
      new->ifFree = 0;
      return (char*)new + blockSize ;
    }else{//need memory, create the head
      next = (struct blockMem*)((char*)new + blockSize);
      next->next = new->next;
      next->size = new->size - blockSize;
      new->size = size;
      next->ifFree = 0;//fail
      new ->ifFree = 0;
      new ->next = next;
	if(new==tail)
		tail=next;
	else
		tail=tail;
	blockInd[getFree()] = next;
      return (char*)new + blockSize;
    }
}while(new != 0);
//saturation situation
//if((new = (struct blockMem*)sbrk(5000+size))==(void *)){
//  return 0;
//}
//if the head if null, means not enough memory
printf("error: not enough memory available from line: %d in file: %s. \n", line, file);
return 0;
  
}

void myfree(void *p, char *file, int line){
  struct blockMem *prev, *ptr, *new;
  ptr = (struct blockMem*)((char*)p-blockSize);

  if(p==NULL){//if the pointer is NULL
    printf("error: free NULL pointer from line: %d in file: %s. \n", line, file);
    return -1;
  }else if(ptr->ifFree){//if the pinter is free==the pointer has never been allocated
    printf("error: can't free not allocated memory from line: %d in file: %s. \n", line, file);
  }else if(freeBlock(ptr)==1){//not free block
    printf("error: can't free memory not in the malloc from line: %d in file: %s. \n", line, file);
  }
}
