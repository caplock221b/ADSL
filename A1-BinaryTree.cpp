//============================================================================
// Name        : A1-BinaryTree.cpp
// Author      : AJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
	Given binary tree with n nodes and perform following operations on
	it.
		a) Assign this tree to another [operator=]
		b) Erase all nodes in a binary tree
		c) Create a mirror image of the tree
		d) Check two binary trees are equal or not
		e) Inorder, Preorder, Postorder traversal of tree(recursive and
		   non-recursive)
		f) Print internal and leaf nodes
*/

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Node{
private:
	int data;
	Node *left;
	Node *right;
public:
	Node(){
		data = 0;
		left = NULL;
		right = NULL;
	}
	friend class BinaryTree;
};

class BinaryTree{
private:
	Node *root;
	Node *mirror;
public:
	BinaryTree(){
		root = NULL;
		mirror = NULL;
    }
	Node* createNode(int data){
		Node *temp = new Node;
		temp->data = data;
		return temp;
	}
	void insertNode(int data){
		Node *p = createNode(data);
		int flag;
		char ch;
		if(root == NULL){
			root = p;
		}
		else{
			Node *q = root;
			flag = 0;
			while(flag != 1){
				cout<<"\nEnter "<<data<<" to the left or right of "<<q->data<<" ? (Enter l for left OR r for right) : ";
				cin>>ch;
				if(ch == 'l'){
					if(q->left == NULL){
						q->left = p;
						flag = 1;
					}
					else
						q = q->left;
				}
				else{
					if(q->right == NULL){
						q->right = p;
						flag = 1;
					}
					else
						q = q->right;
				}
			}
		}
	}
	void inorderIterative(){
        Node *p = root;
        stack <Node*> s;
        int flag = 0;
        cout<<"\n\tThe Binary Tree in inorder form is : ";
        while(flag==0){
        	if(p!=NULL){
        		s.push(p);
        		p = p->left;
        	}
        	else{
        		if(!s.empty()){
        			p = s.top();
        			s.pop();
        			cout<<p->data<<" ";
        			p = p->right;
        		}
        		else
        			flag = 1;
        	}
        }
        cout<<endl;
	}
	void preorderIterative(){
        Node *p = root;
        stack <Node*> s;
        int flag = 0;
        cout<<"\tThe Binary Tree in preorder form is : ";
        while(flag==0){
        	if(p!=NULL){
        		cout<<p->data<<" ";
        		s.push(p);
        		p = p->left;
        	}
        	else{
        		if(!s.empty()){
        			p = s.top();
        			s.pop();
        			p = p->right;
        		}
        		else
        			flag = 1;
        	}
        }
        cout<<endl;
	}
	void postorderIterativeTwoStacks(){
        stack <Node*> s1, s2;
        s1.push(root);
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
            if(s2.top()->left!=NULL)
                s1.push(s2.top()->left);
            if(s2.top()->right!=NULL)
                s1.push(s2.top()->right);
        }
        cout<<"\tThe Binary Tree in postorder form is : ";
        while(!s2.empty()){
            cout<<s2.top()->data<<" ";
            s2.pop();
        }
        cout<<endl;
	}
	void inorderTraversal(Node *p){
		if(p){
			inorderTraversal(p->left);
			cout<<p->data<<" ";
			inorderTraversal(p->right);
		}
	}
	void preorderTraversal(Node *p){
		if(p){
			cout<<p->data<<" ";
			preorderTraversal(p->left);
			preorderTraversal(p->right);
		}
	}
	void postorderTraversal(Node *p){
		if(p){
			postorderTraversal(p->left);
			postorderTraversal(p->right);
			cout<<p->data<<" ";
		}
	}
	void callDisplay(int choice){
		if(choice==1){
			cout<<"\n\tThe Binary Tree in inorder form is : ";
			inorderIterative();
			cout<<"\n\tThe Binary Tree in preorder form is : ";
			preorderIterative();
			cout<<"\n\tThe Binary Tree in postorder form is : ";
			postorderIterativeTwoStacks();
		}
		else{
			cout<<"\n\tThe Binary Tree in inorder form is : ";
			inorderTraversal(root);
			cout<<"\n\tThe Binary Tree in preorder form is : ";
			preorderTraversal(root);
			cout<<"\n\tThe Binary Tree in postorder form is : ";
			postorderTraversal(root);
		}
	}
	void internalLeafPrint(){
		stack <Node*> s;
		queue <int> internal, leaf;
		Node *p = root;
		int flag = 0;
		while(flag == 0){
			if(p!=NULL){
				s.push(p);
				p = p->left;
			}
			else{
				if(!s.empty()){
					p = s.top();
					s.pop();
					p = p->right;
				}
				else{
					flag = 1;
				}
			}
			if(p!=NULL){
				if(p->left!=NULL || p->right!=NULL)
					internal.push(p->data);
				else
					leaf.push(p->data);
			}
		}
		cout<<"\nInternal nodes are : ";
		while(!internal.empty()){
			cout<<internal.front()<<" ";
			internal.pop();
		}
		cout<<"\nLeaf nodes are : ";
		while(!leaf.empty()){
			cout<<leaf.front()<<" ";
			leaf.pop();
		}
	}
    Node* mirrorImage(Node *p){
	    if(p==NULL)
            return p;
        Node *temp = createNode(p->data);
        temp->left = mirrorImage(p->right);
        temp->right = mirrorImage(p->left);
        return temp;
	}
	void createMirrorImage(){
        mirror = mirrorImage(root);
        cout<<"\n\tThe mirrored tree in inorder form is : ";
        inorderTraversal(mirror);
	}
	Node* copyBinaryTree(Node *p){
	    if(p==NULL)
            return p;
        Node *temp = createNode(p->data);
        temp->left = copyBinaryTree(p->left);
        temp->right = copyBinaryTree(p->right);
        return temp;
	}
	void operator = (BinaryTree ob){
        root = copyBinaryTree(ob.root);
	}
	void eraseAllNodes(Node *p){
		if(p == NULL)
			return;
		eraseAllNodes(p->left);
		eraseAllNodes(p->right);
		p->left = NULL;
		p->right = NULL;
		delete p;
	}
	void deleteNodes(){
		eraseAllNodes(root);
		root = NULL;
	}
};

int main() {
	BinaryTree bt, bt2;
	char ch;
	int option, data;
	do{
		cout<<"Menu :\n1. Insert a node in the binary tree\n2. Display the tree\n3. Display internal and leaf nodes\n4. Mirror image of tree\n5. Copy the tree\n6. Erase all nodes\nEnter your choice - 1, 2, 3, 4, 5 or 6 : ";
		cin>>option;
		switch(option){
		case 1:
			cout<<"Enter data to inserted : ";
			cin>>data;
			bt.insertNode(data);
			break;
		case 2:
			cout<<"\t1. Iterative Display\n\t2. Recursive Display\n\tEnter your choice 1 or 2 : ";
			cin>>option;
			switch(option){
			case 1:
				bt.callDisplay(1);
				break;
			case 2:
				bt.callDisplay(2);
				break;
			}
			break;
		case 3:
			bt.internalLeafPrint();
			break;
        case 4:
            bt.createMirrorImage();
            break;
		case 5:
			bt2 = bt;
			bt2.callDisplay(1);
			break;
		case 6:
			bt.deleteNodes();
			cout<<"All the nodes have been deleted."<<endl;
			break;
		default:
			cout<<"Please enter valid option next time."<<endl;
			break;
		}
		cout<<"\nPerform another operation? (Enter y for yes OR n for no) : ";
		cin>>ch;
		cout<<"\n";
	}while(ch != 'n');
	return 0;
}
