#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100000
#define IsFull(ptr)(!(ptr))

typedef struct Node Node;
struct Node{
	struct Node *parent;
	struct Node *left;
	int value;
	struct Node *right;
};

void AddNode(Node *parent, int add_key);
void DeleteNode(Node *parent, int del_key);
Node* FindMin(Node *ptr);
void Print(Node *ptr);

int main(){
	//create root of binary tree
	Node *root;
	root = (Node*)malloc(sizeof(Node));
	//set root' key
	int key = 0;
	scanf("%d", &key);
	if(key < 1 || key > 100){
		printf("The key value is < 1 or > 100.");
		return 0;
	}
	root->value = key;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	printf("add\n");
	//input the rest of key, row 1 in input.txt
	char ch;
	while(1==1){
	printf("add\n");
		scanf("%c", &ch);
		if(ch == '\n')
			break;
		key = ch - '0';
		if(key >= 1 && key <= 100){
			AddNode(root, key);
		}
	}
	//delete the key, row 2 in input.txt
	while(1==1){
		scanf("%c", &ch);
		if(ch == '\n')
			break;
		key = ch - '0';
		if(key >= 1 && key <= 100){
			DeleteNode(root, key);
		}
	}
	//print result to output.txt
	Print(root);	
	return 0;
}

void AddNode(Node *parent, int add_key){
	if(parent)
	{	
		if(add_key < parent->value)
		{
			/* the left child is null */
			if(!parent->left)
			{
				//create new left node
				Node *tpnode = (Node*)malloc(sizeof(Node));
				if(IsFull(tpnode)){
					printf("The memory is full\n");
					exit(1);
				}
				tpnode->value = add_key;
				tpnode->left = NULL;
				tpnode->right = NULL;
				tpnode->parent = parent;
				//add new *node to tree, the left of parent
				parent->left = tpnode;
			}
			else{
				AddNode(parent->left, add_key);
			}
		}
		else if(add_key > parent->value)
		{
			/* the right node is null */
			if(!parent->right)
			{
				//create new right node
				Node *tpnode = (Node*)malloc(sizeof(Node));
				if(IsFull(tpnode)){
					printf("The memory is full\n");
					exit(1);
				}
				tpnode->value = add_key;
				tpnode->left = NULL;
				tpnode->right = NULL;
				tpnode->parent = parent;
				//add new *node to tree, the right of parent
				parent->right = tpnode;
			}
			else{
				AddNode(parent->right, add_key);
			}
		}
	}
};

void DeleteNode(Node *parent, int del_key){
	if(parent)
	{
		if(del_key == parent->value)
		{
			Node *tpnode = (Node*)malloc(sizeof(Node));
			tpnode = parent;
			/* find the node to replace */
			if(parent->left && parent->right)
			{/* two children */
				Node *minnode = (Node*)malloc(sizeof(Node));
				minnode = FindMin(parent->right);
				/* make connect to minnode */
				minnode->parent->left = minnode->right;//cut old , minnode->right can exist or be NULL
				minnode->parent = tpnode->parent;//to new parent
				minnode->left = tpnode->left;
				minnode->right = tpnode->right;
				/*----------------------------*/
				if(tpnode->value < tpnode->parent->value)
					tpnode->parent->left = minnode;
				else if(tpnode->value > tpnode->parent->value)
					tpnode->parent->right = minnode;
				free(tpnode);
				free(minnode);
			}
			else if(parent->left && !parent->right)
			{/* only left child */
				if(tpnode->value < tpnode->parent->value)
					tpnode->parent->left = tpnode->left;
				else if(tpnode->value > tpnode->parent->value)
					tpnode->parent->right = tpnode->left;
				free(tpnode);
			}
			else if(!parent->left && parent->right)
			{/* only right child */
				if(tpnode->value < tpnode->parent->value)
					tpnode->parent->left = tpnode->left;
				else if(tpnode->value > tpnode->parent->value)
					tpnode->parent->right = tpnode->left;
				free(tpnode);
			}
			else
			{/* leaf node */
				if(tpnode->value < tpnode->parent->value)
					tpnode->parent->left = NULL;
				else if(tpnode->value > tpnode->parent->value)
					tpnode->parent->right = NULL;
				free(tpnode);
			}
		}
		else if(del_key < parent->value)
		{
			DeleteNode(parent->left, del_key);
		}
		else if(del_key > parent->value)
		{
			DeleteNode(parent->right, del_key);
		}
	}
};
Node* FindMin(Node *ptr){
	if(ptr->left){
		ptr = FindMin(ptr->left);
		return ptr;
	}
	else{
		return ptr;	
	}
};
void Print(Node *ptr){
	//create queue
	int front = 0, rear = 0;
	Node *queue[MAX_QUEUE_SIZE];
	if(!ptr)
		return; //empty tree
	//add first node to queue
	queue[rear] = ptr;
	while(1 == 1)
	{
		//take node's ptr from queue
		ptr = queue[front];
		front++;
		if(ptr)
		{
			//print the key value
			printf("%d\n", ptr->value);
			//put ptr's children to queue
			if(ptr->left)
			{
				if(rear+1 < MAX_QUEUE_SIZE)
				{
					queue[++rear] = ptr->left;
				}	
			}
			if(ptr->right)
			{
				if(rear+1 < MAX_QUEUE_SIZE)
				{
					queue[++rear] = ptr->right;
				}
			}
		}
		else
			break;
	}
};
