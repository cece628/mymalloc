#ifndef MYMALLOC_H_
#define MYMALLOC_H_

int *mymalloc(int size);
int myblock[5000];
char saved_names[100][20],name[20];
int cnt1,cnt2,x,total,pos,available1,available2,temp;
int saved_sizes[100],saved_pos[100][2];
void myfree(int *p);

#endif
