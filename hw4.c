#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100000
#define IsFull(ptr)(!(ptr))

typedef struct Node Node;
struct Node{
	struct Node *left;
	int value;
	struct Node *right;
};

void AddNode(Node *parent, int add_key);
void DeleteNode(Node *parent, Node *delnode, int del_key);
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
		if(key >= 1 && key <= 100){
			if(key == root->value)
			{/*delete root(delnode)*/
				if(root->left && root->right)
				{
					Node *del = root;
					Node *minnode = NULL, *minparent = NULL;//minnode's parent
					for(minnode = root->right; minnode->left != NULL; minnode = minnode->left){
						if(minnode->left == NULL)
							break;
						minparent = minnode;
					}
					if(minparent)
						minparent->left = minnode->right;//cut, and min's right can exist or be null
					/* take root's children */
					minnode->left = root->left;
					if(minnode == root->right)
						minnode->right = NULL;
					else
						minnode->right = root->right;
					root = minnode;
					free(del);
				}		
				else if(root->left && !root->right)
				{
					Node *del = root;
					root = root->left;
					free(del);
				}
				else if(!root->left && root->right)
				{
					Node *del = root;
					root = root->right;
					free(del);
				}
				else
					free(root);
			}
			else if(key < root->value)
				DeleteNode(root, root->left, key);
			else if(key > root->value)
				DeleteNode(root, root->right, key);
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
				//add new *node to tree, the right of parent
				parent->right = tpnode;
			}
			else{
				AddNode(parent->right, add_key);
			}
		}
	}
};

void DeleteNode(Node *parent, Node *delnode, int del_key){
	if(delnode)
	{
		if(del_key == delnode->value)
		{
			/* find the node to replace */
			if(delnode->left && delnode->right)
			{/* two children */
				/* find min node of right' sub tree */
				Node *minnode = NULL, *minparent = NULL;//minnode's parent
				for(minnode = delnode->right; minnode->left != NULL; minnode = minnode->left){
					if(minnode->left == NULL)
						break;
					minparent = minnode;
				}
				if(minparent)
					minparent->left = minnode->right;//cut, and min's right can exist or be null
				/* take delnode's children */
				minnode->left = delnode->left;
				if(minnode == delnode->right)
					minnode->right = NULL;
				else
					minnode->right = delnode->right;
				/***************************/
				if(minnode->value < parent->value)
					parent->left = minnode;
				else if(minnode->value > parent->value)
					parent->right = minnode;
				free(delnode); 				
			}
			else if(delnode->left && !delnode->right)
			{/* only left child */
				if(delnode->value < parent->value)
					parent->left = delnode->left;
				else if(delnode->value > parent->value)
					parent->right = delnode->left;
				free(delnode);
			}
			else if(!delnode->left && delnode->right)
			{/* only right child */
				if(delnode->value < parent->value)
					parent->left = delnode->right;
				else if(delnode->value > parent->value)
					parent->right = delnode->right;
				free(delnode);
			}
			else
			{/* leaf node */
				if(delnode->value < parent->value)
					parent->left = NULL;
				else if(delnode->value > parent->value)
					parent->right = NULL;
				free(delnode);
			}
		}
		else if(del_key < delnode->value)
		{
			DeleteNode(delnode, delnode->left, del_key);
		}
		else if(del_key > delnode->value)
		{
			DeleteNode(delnode, delnode->right, del_key);
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
