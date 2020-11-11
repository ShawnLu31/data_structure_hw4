# data_structure_hw4
## Result screenshot
* compile
![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/compile.JPG)
* execution
![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/execution.JPG)
* result
![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/diff.JPG)
## Program structure
![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/structure.png)
## Program design
node structure:
```c
typedef struct Node Node;
struct Node{
	struct Node *left; //pointer to left child
	int value;
	struct Node *right; //pointer to right child
};
 ```
## Program functions
1. void AddNode(Node *parent, int add_key);
	* parameter
		* Node *parent: the parent of the node that is going to be added.
		* int add_key: the key that is going to be added into the tree.
		* Description:  
		if add_key is smaller than parent's key the add_key is put on the left side of parent.  
		if add_key is bigger than parent's key the add_key is put on the right side of parent.  
		* e.g.
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/add1.JPG)
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/add2.JPG)
2. void DeleteNode(Node *parent, Node *delnode, int del_key);
	* parameter
		* Node *parent: the parent of the node that is going to be deleted.
		* Node *delnode: the node that is going to be deleted.
		* int del_key: the key that is going to be deleted from the tree.
	* Description:  
	four situation:
	1. del_node is leaf node:
		* Make the parent's child pointer that pointed to leaf node point to null.
		* e.g.
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/leaf1.JPG)
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/leaf2.JPG)
	2. del_node has only left child:
		* Make the parent's child pointer that pointed to del_node point to del_node's left child.
		* The left child might exist or be null.
		* e.g.
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/left1.JPG)
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/left2.JPG)
	3. del_node has only right child:
		* Make the parent's child pointer that pointed to del_node point to del_node's right child.
		* The rightt child might exist or be null.
		* e.g.
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/right1.JPG)
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/right2.JPG)
	4. del_node has two children:
		* Find the smallest key in del_node's rigth subtree.
		* Replace del_node with the smallest key's node.
		* parameter :
			* minnode : the node has the smallest key of th delnode's right subtree.
			* minparent : parent of the minnode.  
		* e.g.
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/two1.JPG)
		![image](https://github.com/ShawnLu31/data_structure_hw4/blob/main/two2.JPG)
3. void Print(Node *ptr);
	* parameter
		* Node *ptr
	* Description:
		* This function will print out the node of the subtree of *ptr* in **Level Order**.
		* It prints the whole binary search tree when *ptr* is *root*.
