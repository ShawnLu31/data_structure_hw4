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
void DeleteNode(Node *delnode, int del_key);
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
	//input the rest of key, row 1 in input.txt
	char ch;
	while(scanf("%c", &ch) != EOF){
		if(ch == '\n')
			break;
		key = ch - '0';
		if(key >= 1 && key <= 100)
			AddNode(root, key);
	}
	//delete the key, row 2 in input.txt
	while(scanf("%c", &ch) != EOF){
		if(ch == '\n')
			break;
		key = ch - '0';
		if(key >= 1 && key <= 100)
			DeleteNode(root, key);
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

void DeleteNode(Node *delnode, int del_key){
	if(delnode)
	{
		if(del_key == delnode->value)
		{
			/* find the node to replace */
			if(delnode->left && delnode->right)
			{/* two children */
				/* find min node of right' sub tree */
				Node *minnode;
				for(minnode = delnode->right; minnode->left != NULL; minnode = minnode->left)
					if(minnode->left == NULL)
						break;
				/* make connect to minnode */
				if(minnode->parent == delnode)
				{
					//min's parent is delnode == min is delnode's right child
					minnode->parent = delnode->parent;//new parent
					minnode->left = delnode->left;//take delnode's left
					/* update delnode's children's parent*/
					delnode->left->parent = minnode;
				}	
				else
				{
					//min's parent is not delnode == min is not delnode's right child
					minnode->parent->left = minnode->right;//cut old , minnode->right can exist or be NULL
					minnode->parent = delnode->parent;//new parent
					minnode->left = delnode->left;//take delnode's left
					minnode->right = delnode->right;//take delnode's right 
					/* update delnode's children's parent*/
					delnode->left->parent = minnode;
					delnode->right->parent = minnode;
				}
				/* make the parent connect to minnode */
				if(minnode->value < minnode->parent->value)
					minnode->parent->left = minnode;
				else if(minnode->value > minnode->parent->value)
					minnode->parent->right = minnode;
				free(delnode); 				
			}
			else if(delnode->left && !delnode->right)
			{/* only left child */
				if(delnode->value < delnode->parent->value)
					delnode->parent->left = delnode->left;
				else if(delnode->value > delnode->parent->value)
					delnode->parent->right = delnode->left;
				delnode->left = delnode->parent;
				free(delnode);
			}
			else if(!delnode->left && delnode->right)
			{/* only right child */
				if(delnode->value < delnode->parent->value)
					delnode->parent->left = delnode->right;
				else if(delnode->value > delnode->parent->value)
					delnode->parent->right = delnode->right;
				delnode->right = delnode->parent;
				free(delnode);
			}
			else
			{/* leaf node */
				if(delnode->value < delnode->parent->value)
					delnode->parent->left = NULL;
				else if(delnode->value > delnode->parent->value)
					delnode->parent->right = NULL;
				free(delnode);
			}
		}
		else if(del_key < delnode->value)
		{
			DeleteNode(delnode->left, del_key);
		}
		else if(del_key > delnode->value)
		{
			DeleteNode(delnode->right, del_key);
		}
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
			printf("%d", ptr->value);
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
			if(queue[front] != NULL)
				printf("\n");
		}
		else
			break;
	}
};
