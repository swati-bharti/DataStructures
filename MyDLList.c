// Author: SWATI BHARTI
// Student ID: Z5277828
// Platform: Mac
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
	int  value;  // value (int) of this list item 
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
	int  size;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	DLList *L;

	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here:O(n)
DLList *CreateDLListFromFileDlist(const char *filename)
{
 // put your code here
 char str[BUFSIZ];
 DLList *L = newDLList();
 if(!strcmp(filename,"stdin")){
	 while(scanf("%s",str)){

  if(!strcmp(str,"end")){
	  return L;
  }	
	
  int check=0;
  int i=0;
  int val;
  int count =0;
  for(i=0;i<strlen(str);i++)
  {
	  if(str[i]=='-'){
		  if(count==0)
		  	{count++;
			continue;}
		  else
		  {
			  check=1;
			  break;
		  }
		  
	  }
	  if(!isdigit(str[i]))
	  {
		  check=1;
	  }
  }	  
if (check==0)
{
	val=atoi(str);
	 
	 DLListNode *new = newDLListNode(val);
	 if (L->size==0){
		 L->first=new;
		 L->last=new;
		 L->size++;

	 }
	 else{
		 L->last->next=new;
		 new->prev=L->last;
		 L->last=new;
		 L->size++;

	 }
	
}
	else
	{
		printf("invalid input");/* code */
		exit(1);
	}
  
}
 }
 FILE *fp;
 fp =fopen(filename,"r");
 	if(fp==NULL)
	{
		printf("cannot open the file\n");
		exit(1);

	}
	 
	while(fscanf(fp,"%s",str)!=EOF){

	
	
  int check=0;
  int i=0;
  int val;
  int count =0;
  for(i=0;i<strlen(str);i++)
  {
	  if(str[i]=='-'){
		  if(count==0)
		  	{count++;
			continue;}
		  else
		  {
			  check=1;
			  break;
		  }
		  
	  }
	  if(!isdigit(str[i]))
	  {
		  check=1;
	  }
  }	  
if (check==0)
{
	val=atoi(str);
	// while(fscanf(fp,"%d",val)!=EOF){
	 
	 DLListNode *new = newDLListNode(val);
	 if (L->size==0){
		 L->first=new;
		 L->last=new;
		 L->size++;

	 }
	 else{
		 L->last->next=new;
		 new->prev=L->last;
		 L->last=new;
		 L->size++;

	 }
	

//  }
	
}
else
{
	printf("invalid input");/* code */
	exit(1);
}

  
}
return L;
}
 







// clone a DLList
// put your time complexity analysis for cloneList() here:O(n)
DLList *cloneList(DLList *u)
{
 // put your code here
 if(u==NULL){
	 return NULL;

	  
 }

 DLListNode *ptr = u->first;
 DLList *k = newDLList();
 while(ptr!=NULL){
	
	DLListNode *new1 = newDLListNode(ptr->value);
	if (k->size==0){
		k->first=new1;
		k->last=new1;
		k->size++;
		
	}
	else{
		k->last->next=new1;
		new1->prev=k->last;
		k->last=new1;
		k->size++;
	}

	 ptr=ptr->next;
	 

 }

	  
 return k;
}

// compute the union of two DLLists u and v
// put your time complexity analysis for union() here:O(mn)
DLList *setUnion(DLList *u, DLList *v)
{
 // put your code here
 if(u==NULL){
		return v ;
	}
	if(v==NULL){
		return u ;
	}
DLListNode *ptr2 = v->first;
while(ptr2!=NULL){
	int check =0;
	DLListNode *ptr3 = u->first;
	while (ptr3!=NULL){
		if(ptr2->value==ptr3->value){
			check=1;
		}
		ptr3=ptr3->next;
	}
	if(check==0)
	{
			DLListNode *new1 = newDLListNode(ptr2->value);
			u->last->next= new1;
			new1->prev = u->last;
			u->last=new1;
			}
	ptr2=ptr2->next;	
	}
    return u;
}


// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here:O(mn)
DLList *setIntersection(DLList *u, DLList *v)
{
	DLList *k = newDLList();
	if(u==NULL){
		return NULL ;
	}
	if(v==NULL){
		return NULL ;
	}
  // put your code here
  DLListNode *ptr = v->first;
  while(ptr!=NULL){
	DLListNode *ptr1=u->first;
	while(ptr1!=NULL){
		if(ptr1->value==ptr->value){
			DLListNode *new1 = newDLListNode(ptr->value);
			if (k->size==0){
				k->first=new1;
				k->last=new1; 
				k->size++;
				
			}
			else{
				k->last->next=new1;
				new1->prev=k->last;
				k->last=new1;
				k->size++;
			}
			}
		ptr1=ptr1->next;	
		}
	ptr=ptr->next;
  }
return k;
}
// free up all space associated with list
// put your time complexity analysis for freeDLList() here:O(n)
void freeDLList(DLList *L)
{
DLListNode *h = L->first;
// put your code here	
while(h!=NULL){
	L->first=L->first->next;
	free(h);
	h=L->first;

}
}


// display items of a DLList
// put your time complexity analysis for printDDList() here:O(n)
void printDLList(DLList *u)
{
	if(u==NULL){
		return;
	}
	DLListNode *printNode = u->first; 
	while(printNode!=NULL){

		 printf("%d\n",printNode->value);
		 printNode=printNode->next;

	}
}

int main()
{
 DLList *list1, *list2, *list3, *list4;

 list1=CreateDLListFromFileDlist("File1.txt");
 printDLList(list1);

 list2=CreateDLListFromFileDlist("File2.txt");
 printDLList(list2);

 list3=setUnion(list1, list2);
 printDLList(list3);

 list4=setIntersection(list1, list2);
 
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 printf("please type all the integers of list1\n");
 list1=CreateDLListFromFileDlist("stdin");

 printf("please type all the integers of list2\n");
 list2=CreateDLListFromFileDlist("stdin");
 
 list3=cloneList(list1);
 printDLList(list3);
 list4=cloneList(list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 return 0; 
}
