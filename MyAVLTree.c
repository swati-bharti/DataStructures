#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data type for avl tree nodes
typedef struct AVLTreeNode {
	int key; //key of this item
	int  value;  //value (int) of this item 
	int height; //height of the subtree rooted at this node
	struct AVLTreeNode *parent; //pointer to parent
	struct AVLTreeNode *left; //pointer to left child
	struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree{
	int  size;      // count of items in avl tree
	AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
	AVLTreeNode *new;
	new = malloc(sizeof(AVLTreeNode));
	assert(new != NULL);
	new->key = k;
	new->value = v;
	new->height = 0; // height of this new node is set to 0
	new->left = NULL; // this node has no child
	new->right = NULL;
	new->parent = NULL; // no parent
	return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);
	T->size = 0;
	T->root = NULL;
	return T;
}
int InsertNode(AVLTree *T, int k, int v);
AVLTreeNode *insert(AVLTreeNode*,int,int);
void PrintAVLTree(AVLTree *T);
// put your time complexity analysis of CreateAVLTree()here:O(nlogn)
AVLTree *CreateAVLTree(const char *filename)
{

 // put your code here

 int k,v,j;
 char c;
 FILE *fp;
 AVLTree *T = newAVLTree();
 if(strcmp(filename,"stdin")==0){
	 while(scanf("%c",&c))
{
	if(c=='('){
	scanf("%d, %d)",&k,&v);
	// printf("%d,%d\n",k,v);
	InsertNode(T,k,v);
	// PrintAVLTree(T);
	} else if (c==' ' ||c=='\n' || c=='\r'){
		continue;
	}else{
		break;
	}

}
return T;

 }
 fp=fopen(filename,"r");
 if(fp==NULL)
	{
		printf("cannot open the file\n");
		exit(1);

	}
while(fscanf(fp,"%c",&c)!=EOF)
{
	if(c=='('){
	fscanf(fp,"%d, %d)",&k,&v);
	// printf("%d,%d\n",k,v);
	InsertNode(T,k,v);
	// PrintAVLTree(T);
	} else if (c==' ' ||c=='\n' || c=='\r'){
		continue;
	}else{
		break;
	}

}

fclose(fp);
return T;
  
}
void cloneNodes(AVLTreeNode *node,AVLTree *cloneTree){
	if(node==NULL)
	{
		return;
	}
	cloneTree->root = insert(cloneTree->root,node->key,node->value);
	cloneNodes(node->left,cloneTree);
	cloneNodes(node->right,cloneTree);
}

// // put your time complexity analysis for CloneAVLTree() here:O(n)
 AVLTree *CloneAVLTree(AVLTree *T)
{
//  // put your code here
AVLTree *cloneTree = newAVLTree();
if(T==NULL)
 {
	 return NULL;
 }
 
 if(T->root==NULL)
 {
	 return cloneTree;
 }
 cloneNodes(T->root,cloneTree); 
 return cloneTree;
  
}
 
// // put your time complexity for ALVTreesUNion() here
 AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2)
{ 
		//put your code here
 }

 
// // put your time complexity for ALVTreesIntersection() here
 AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2)
 {
 	 //put your code here
}

AVLTreeNode *insert(AVLTreeNode *node,int k,int v){
	if(node==NULL){
		node = newAVLTreeNode(k,v);
		// printf("%d\n",node->key);
		return node;
	}
	if(k<node->key){
		node->left  = insert(node->left,k,v);
		node->left->parent = node;
		return node;
		}
	else if (k>node->key) {
        node->right = insert(node->right,k,v);
		node->right->parent = node;
		return node;
	}
	else if(k==node->key){
		if(v<node->value){
			node->left  = insert(node->left,k,v);
			node->left->parent = node;	
			return node;
		}
		else
		{
			node->right = insert(node->right,k,v);
			node->right->parent = node;
		return node;
		}
	}
}
int max(int a, int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}
int height(AVLTreeNode *node)
{	
	if(node->left==NULL && node->right==NULL){
		node->height=0;
		// printf("h1 %d\n",node->key);
		return 0;
	}
	if(node->left==NULL && node->right!=NULL){
		node->height=height(node->right)+1;
		// printf("h2 %d\n",node->key);
		return node->height;
	}
	if(node->right==NULL && node->left!=NULL){
		node->height=height(node->left)+1;
		// printf("h3 %d\n",node->key);
		return node->height;
	}
	int h1 = height(node->left);
	int h2 = height(node->right);
	 
	node->height=max(h1,h2)+1;
	// printf("h4 %d\n",node->key);
	return node->height;
}
AVLTreeNode *balance(AVLTreeNode *node){
	AVLTreeNode *j;
	if(node==NULL){
		return NULL;
	}
	if(node->right==NULL && node->left==NULL){
		return NULL;
}
	if(node->right!=NULL){ 
		j=balance(node->right);
		if(j!=NULL){
			return j;
		}

	}
	if(node->left!=NULL){
		j=balance(node->left);
		if(j!=NULL){
			return j;
		}
	}

	if(node->left==NULL && node->right->height>0){
		return node;
	}
	if(node->right==NULL && node->left->height>0){
		return node;
	}
	if(node->left && node->right && abs(node->left->height-node->right->height)>1){
		return node;
	}
	return NULL;
	}
	
	void rotateleft(AVLTreeNode *node){
		node->right->parent=node->parent;
		if (node->parent!=NULL)
		{
			if(node->parent->right==node){
				node->parent->right=node->right;
			}
			else
			{
				node->parent->left=node;
			}
			
		}
		node->parent=node->right;
		AVLTreeNode *temp = node->right;
		node->right=node->right->left;
		temp->left=node;
		
	}
	void rotateright(AVLTreeNode *node){
		node->left->parent=node->parent;
		  if(node->parent!=NULL)
		  {
			  if(node->parent->right==node){
				node->parent->right=node->left;
			}
			else
			{
				node->parent->left=node->left;
			}
			
		  }
		  node->parent=node->left;
		  AVLTreeNode *temp = node->left;
		  node->left=node->left->right;
		  temp->right=node;
		
	}

	void rotaterightleft(AVLTreeNode *node){
		rotateright(node->right);
		rotateleft(node);

	}
		
  	void rotateleftright(AVLTreeNode *node){
		rotateleft(node->left);
		rotateright(node);
	}

	void checkingrotation(AVLTreeNode *node){
		
		AVLTreeNode *n = node;
	if(((n->left == NULL) && (n->right)) || ((n->right) &&(n->right->height>n->left->height))){
		n = n->right;
		if(((n->left == NULL) && (n->right)) || ((n->right) && (n->right->height>n->left->height)))
			{
				rotateleft(node);
				return;
				}
		if(((n->right == NULL) && (n->left)) || ((n->left) && (n->left->height>n->right->height)))
			{
				rotaterightleft(node);
				return;
				}
		else {
			rotaterightleft(node);
		}
	
	}
	else if(((n->right == NULL) && (n->left)) || ((n->left) && (n->left->height>n->right->height))){
		n = n->left;
		if(((n->right == NULL) && (n->left)) || ((n->left) && (n->left->height>n->right->height)))
			{
				rotateright(node);
				return;
			}
		if(((n->left == NULL) && (n->right)) || ((n->right)&&(n->right->height>n->left->height)))
			{
				rotateleftright(node);
				return;
			}
		else{
			rotateleftright(node);
			return;
		}
	}
	}
	
	
	

// // put the time complexity analysis for InsertNode() here :O(log n)   
 int InsertNode(AVLTree *T, int k, int v)
 {
// 	//put your code here;
//  if(Search(T,k,v))
// 	return 0;
 T->root=insert(T->root,k,v);
 
  int h = height(T->root);
   
 AVLTreeNode *j=balance(T->root);
//  PrintAVLTree(T);
 while(j!=NULL){
	//  printf("Insert func: %d,%d->%d\n",j->key,j->value,j->height);
	 checkingrotation(j);
	//  printf("Insert func: %d->%d\n",j->key,j->height);
	 
	 while(T->root->parent!=NULL){
		 T->root = T->root->parent;
		//  printf("%d,%d\n",T->root->key,T->root->value);
	 }
	 h = height(T->root);
	 j = balance(T->root);
 }

// printf("%d\n",T->root->key); 

 }
 AVLTreeNode *mini(AVLTreeNode *node){
	if(node->left==NULL)
	{
		return node;
	}
	else
	{
		
		return mini(node->left);
	}
	
 }
  AVLTreeNode *maxi(AVLTreeNode *node){
	if(node->right==NULL)
	{
		return node;
	}
	else
	{
		
		return mini(node->right);
	}
	
 }
   
   


 

  
int delete(AVLTreeNode *node,int k,int v){
	if(node==NULL){
		return 0;
	}
	if(k<node->key){
		return delete(node->left,k,v);
	}else if(k>node->key){
		return delete(node->right,k,v);
	}
	else if(k==node->key){
		if(node->value > v){
			return delete(node->left,k,v);
		}
		else if(node->value<v){
			return delete(node->right,k,v);
		}
		else if(node->value == v){
			if (node->left==NULL && node->right==NULL){
				if(node->parent){
					if(node->parent->right==node){
						node->parent->right=NULL;
				}else
				{
					node->parent->left=NULL;
				}
				free(node);
				return 1;	
				}else{
					free(node);
					return 1;
					}
				}
			if (node->left==NULL && node->right){
				AVLTreeNode *temp = mini(node->right);
				node->key=temp->key;
				node->value = temp->value;
				return delete(node->right,node->key,node->value);
			}
			else{
				AVLTreeNode *temp = maxi(node->left);
				node->key = temp->key;
				node->value = temp->value;
				return delete(node->left,node->key,node->value);
			}
		}
	}
	

}
// // put your time com plexity for DeleteNode() here:O(log n)
int DeleteNode(AVLTree *T, int k, int v)
	{
		delete(T->root,k,v);
 	}
AVLTreeNode *searchfunc(AVLTreeNode *node,int k,int v){

	if(node==NULL){
		return NULL;
	}
	if(node->key==k && node->value==v)
	{
		return node;
	}
	if(k>node->key){
		return searchfunc(node->right,k,v);
	}
	if(k<node->key){
		return searchfunc(node->left,k,v);
	}
	if(node->key==k && node->value!=v){
		if(v<node->value){
			return searchfunc(node->left,k,v)	;
		}
		if(v>node->value){
			return searchfunc(node->right,k,v);
		}
	}	
}


void freenodes(AVLTreeNode *node){
	if(node==NULL)
	{
		return;
		}
	
	if(node->left==NULL && node->right==NULL){
		freenodes(node);
		return;
	}
	freenodes(node->left);
	freenodes(node->right);
	freenodes(node);
	return;
}


// // put your time complexity analysis for Search() here:O(log n)
AVLTreeNode *Search(AVLTree *T, int k, int v)
 {
   // put your code here
  T->root= searchfunc(T->root,k,v);
 }

// put your time complexity analysis for freeAVLTree() here:O(n)
void FreeAVLTree(AVLTree *T)
{
// put your code here	
if (T->root==NULL){
	return;
}
else{
	freenodes(T->root);
}
}
void printfunc(AVLTreeNode *node)
{	
	if(node == NULL){
		return;
	}
	
    
    printf("%d, %d,-> %d\n", node->key,node->value,node->height); 
    
	printfunc(node->left); 
	printfunc(node->right); 
    
} 



// put your time complexity analysis for PrintAVLTree() here:O(n)
void PrintAVLTree(AVLTree *T)
{
 // put your code here
	printfunc(T->root);
 
}

int main() //sample main for testing 
{ int i,j;
 AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
 AVLTreeNode *node1;
 
tree1=CreateAVLTree("stdin");
 PrintAVLTree(tree1);
FreeAVLTree(tree1);
//  //you need to create the text file file1.txt
//  // to store a set of items without duplicate items
 tree2=CreateAVLTree("file1.txt"); 
 PrintAVLTree(tree2);
tree3=CloneAVLTree(tree2);
PrintAVLTree(tree3);
FreeAVLTree(tree2);
FreeAVLTree(tree3);
//  //Create tree4 
tree4=newAVLTree();
j=InsertNode(tree4, 10, 10);
for (i=0; i<15; i++)
	{
    j=InsertNode(tree4, i, i);
    if (j==0) printf("(%d, %d) already exists\n", i, i);
   }
   PrintAVLTree(tree4);
   node1=Search(tree4,20,20);
   if (node1!=NULL)
     printf("key= %d value= %d\n",node1->key,node1->value);
   else 
     printf("Key 20 does not exist\n");
  
   for (i=17; i>0; i--)
      {
     j=DeleteNode(tree4, i, i);
 	if (j==0) 
 	  printf("Key %d does not exist\n",i);  
     PrintAVLTree(tree4);
   }
 FreeAVLTree(tree4);
//  //Create tree5
  tree5=newAVLTree();
  j=InsertNode(tree5, 6, 25);
  j=InsertNode(tree5, 6, 10);
  j=InsertNode(tree5, 6, 12);
  j=InsertNode(tree5, 6, 20);
  j=InsertNode(tree5, 9, 25);
  j=InsertNode(tree5, 10, 25);
  PrintAVLTree(tree5);
  //Create tree6
  tree6=newAVLTree();
  j=InsertNode(tree6, 6, 25);
  j=InsertNode(tree6, 5, 10);
  j=InsertNode(tree6, 6, 12);
  j=InsertNode(tree6, 6, 20);
  j=InsertNode(tree6, 8, 35);
  j=InsertNode(tree6, 10, 25);
  PrintAVLTree(tree6);
  //tree7=AVLTreesIntersection(tree5, tree6);
  //tree8=AVLTreesUnion(tree5,tree6);
 //PrintAVLTree(tree7);
  //PrintAVLTree(tree8);
 return 0; 
}
