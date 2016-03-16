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
#define numOfBlock (memSize/blockSize+1)

//use link list to access each block of memory, move to .h file
//get size


static void *blockInd[memSize/blockSize+1];
static char block[memSize];


static int i=0;

//check if have free block to re-use free space
int freeBlock(blockMem *ptr){
  int ifFree = 0; //not free at first
  for(i=0;i< (numOfBlock);i++){
    if(ptr == blockInd[i] && !ptr->ifFree){
	ifFree = 1;//already free
      	return 0; 
	}
  }
  return 1;//no freeBlock
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


  if(!firstCall){//fist call
    //use head for the beginning of the block
    //creat the whole block
    head = (struct blockMem*)block;
    head->prev=head->next=0;
    head->size=memSize-blockSize;
    blockInd[getFree()] = block;
    firstCall=1;
    head->ifFree=1;
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
	
      	if (size < (memSize/4)){
			next = (struct blockMem*)((char*)new + blockSize + size);
	}
	if (size >= (memSize/4)){
			next = (struct blockMem*)((memSize/2)+(char*)new + blockSize + size);
	}
      next->prev = new;
      next->next = new->next;
      if(new->next!=0){	//cause core dumped
		new->next->prev=next;
      }
      
      new ->next = next;
      next->size = new->size - blockSize-size;//unallocated memory
      new->size = size;
      next->ifFree = 1;//next chunk has not been freed
      new ->ifFree = 0;
      
	if(new==tail)
		tail=next;
	else
		tail=tail;
      blockInd[getFree()] = next;
      return (char*)new + blockSize;
    }
}while(new != 0);

//-------------saturation situation, when we have to allocates all of the dynamic memory---------------------------------------------------

if(tail == 0){
	new->prev=new->next=0;
	new->size=size;
	new->ifFree=0;
	head=tail=new;
	return (char *)new + blockSize;
}else{
	new->prev=tail;
	new->next=tail->next;
	new->size=size;
	new->ifFree=0;
	tail->next=new;
	tail=new;
	return (char *)new+blockSize;
}
if ((new = (struct blockMem*)sbrk(blockSize + size)) == (void *)-1) {
		return 0;
	}

printf("error: not enough memory available from line: %d in file: %s. \n", line, file);
return 0;
  
}

//-----------extra credit: calloc------------------//
void *mycalloc(int cal, unsigned int size, char *file, int line){
	void *ptr = mymalloc(cal*size, file, line);

	if(ptr){//copy the characters to the memory
		memset(ptr, '0', cal*size);
		return ptr;
	}
}
//--------------extra credit: realloc--------------//
void *myrealloc(void *p, unsigned int size, char *file, int line){
	void *rea;
	rea = mymalloc(size, file, line);
	if(!p){ 
		printf("error: realloc to NULL from line: %d in file: %s.\n", file, line); 
		return(-1);
	}
	else if(p){
		memcpy(rea, p, size);
		myfree(p, file, line);
	}
	return rea;
}
//-------------------------------------------------


void myfree(void *p, char *file, int line){
  struct blockMem *ptr, *pre, *next;
  ptr = (struct blockMem*)((char*)p-blockSize);
  

  if(p==NULL){//if the pointer is NULL
    printf("error: free NULL pointer from line: %d in file: %s. \n", line, file);
    return 0;
  }


  if(freeBlock(ptr)==1){//memory is not allocated in file
	printf("error: not in the malloc from line: %d in file: %s. \n", line, file);
	return;
   }

  if(ptr->ifFree){//if the pinter is free==the pointer has never been allocated
    printf("error: can't free not allocated memory from line: %d in file: %s. \n", line, file);
  }

  if((pre=ptr->prev)!=0 && pre->ifFree){//the previous memory is free, add this to the current free memory
	//blockInd[i] = 0;
	pre->size += blockSize+ptr->size;
	pre->next = ptr->next;
	if(ptr->next != 0){
		ptr->next->prev = pre;
	}
	blockInd[i] = 0;
  }else{//move to the next pointer, ifFree is 1
	ptr->ifFree=1;
	pre=ptr;
  }
  if((next=ptr->next)!=0 && next->ifFree){//merge
	pre->size += blockSize + next->size;
	pre->next = next->next;
	if(next->next != 0){
		next->next->prev = pre;
	}
  }
  for(i=0; i<(numOfBlock);i++){//if the pointer in blockMem exists
		if(next=blockInd[i] && !ptr->ifFree){
			blockInd[i]=0;
			break;
		}
   }
   
}

