//============================================================================
// Name        : A8-AVLTree.cpp
// Author      : AJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
	A Dictionary stores keywords & its meanings. Provide facility for
	adding new keywords, deleting keywords, updating values of any
	entry. Provide facility to display whole data sorted in ascending/
	descending order. Also find how many maximum comparisons may
	require for finding any keyword. Use Height balance tree and find
	the complexity for finding a keyword.
*/

#include <iostream>
using namespace std;

class Node{
private:
	string word;
	string meaning;
	Node *left;
	Node *right;
	int height;
public:
	Node(){
		word = meaning = "";
		left = right = NULL;
		height = 0;
	}
	friend class AVLTree;
};

class AVLTree{
private:
	Node *root;
public:
	AVLTree(){
		root = NULL;
	}
	void createTree(string w, string m){
		root = insert(root, w, m);
	}
	Node* insert(Node *p, string w, string m){
		if(p == NULL){
			p = new Node;
			p->word = w;
			p->meaning = m;
			p->left = p->right = NULL;
		}
		else{
			if(w<p->word){
				p->left = insert(p->left, w, m);
				if(balanceFactor(p) == 2){
					if(w < p->left->word)
						p = LL(p);
					else
						p = LR(p);
				}
			}
			else{
				p->right = insert(p->right, w, m);
				if(balanceFactor(p) == -2){
					if(w > p->right->word)
						p = RR(p);
					else
						p = RL(p);
				}
			}
		}
		p->height = getHeight(p);
		return p;
	}
	int balanceFactor(Node *t){
		int lh, rh;
		if(t == NULL)
			return 0;
		if(t->left == NULL)
			lh = 0;
		else
			lh = 1 + t->left->height;
		if(t->right == NULL)
			rh = 0;
		else
			rh = 1 + t->right->height;
		return (lh-rh);
	}
	int getHeight(Node *t){
		int lh, rh;
		if(t == NULL)
			return 0;
		if(t->left == NULL)
			lh = 0;
		else
			lh = 1 + t->left->height;
		if(t->right == NULL)
			rh = 0;
		else
			rh = 1 + t->right->height;
		return (lh>=rh) ? lh : rh;
	}
	Node* RR(Node *t){
		t = leftRotate(t);
		return t;
	}
	Node* LL(Node *t){
		t = rightRotate(t);
		return t;
	}
	Node* LR(Node *t){
		t->left = leftRotate(t->left);
		t = rightRotate(t);
		return t;
	}
	Node* RL(Node *t){
		t->right = rightRotate(t->right);
		t = leftRotate(t);
		return t;
	}
	Node* leftRotate(Node *p){
		Node *q = p->right;
		p->right = q->left;
		q->left = p;
		p->height = getHeight(p);
		q->height = getHeight(q);
		return q;
	}
	Node* rightRotate(Node *p){
		Node *q = p->left;
		p->left = q->right;
		q->right = p;
		p->height = getHeight(p);
		q->height = getHeight(q);
		return q;
	}
	void inorderTraversal(Node *p){
		if(p!=NULL){
			inorderTraversal(p->left);
			cout<<"\t"<<p->word<<"\t"<<p->meaning<<endl;
			inorderTraversal(p->right);
		}
	}
	void ascendingOrderDisplay(){
		cout<<"The contents of the Dictionary in ascending order are :"<<endl;
		cout<<"\tWord\tMeaning"<<endl;
		inorderTraversal(root);
	}
	void reverseInorderTraversal(Node *p){
		if(p!=NULL){
			reverseInorderTraversal(p->right);
			cout<<"\t"<<p->word<<"\t"<<p->meaning<<endl;
			reverseInorderTraversal(p->left);
		}
	}
	void descendingOrderDisplay(){
		cout<<"The contents of the Dictionary in descending order are :"<<endl;
		cout<<"\tWord\tMeaning"<<endl;
		reverseInorderTraversal(root);
	}
	void searchEntry(){
		string data;
		cout<<"Enter the data to be searched in dictionary : ";
		cin>>data;
		Node *p = root;
		int flag = 0;
		int comparisons = 0;
		while(flag == 0){
			comparisons++;
			if(p->word == data){
				cout<<"Search Successful! Data is present as an entry in the Dictionary."<<endl;
				cout<<"Total number of comparisons : "<<comparisons<<endl;
				flag = 1;
			}
			else if(p->word > data){
				if(p->left != NULL){
					p = p->left;
				}
				else{
					cout<<"Search Failed! Data not present as an entry in the Dictionary."<<endl;
					cout<<"Total number of comparisons : "<<comparisons<<endl;
					flag = 1;
				}
			}
			else{
				if(p->right != NULL){
					p = p->right;
				}
				else{
					cout<<"Search Failed! Data not present as an entry in the Dictionary."<<endl;
					cout<<"Total number of comparisons : "<<comparisons<<endl;
					flag = 1;
				}
			}
		}
	}
};

int main() {
	AVLTree avl;
	int choice;
	char ans;
	string w, m;
	do{
		cout<<"Menu:\n1. Insert a word into the dictionary\n2. Display in alphabetical order\n3. Display in reverse order\n4. Search for a word in the dictionary\nEnter your choice 1, 2, 3 or 4 : ";
		cin>>choice;
		switch(choice){
		case 1:
			cout<<"Enter the word to be entered into the dictionary : ";
			cin>>w;
			cin.ignore();
			cout<<"Enter it's meaning : ";
			getline(cin, m);
			avl.createTree(w, m);
			break;
		case 2:
			avl.ascendingOrderDisplay();
			break;
		case 3:
			avl.descendingOrderDisplay();
			break;
		case 4:
			avl.searchEntry();
			break;
		default:
			cout<<"Please enter valid choice next time."<<endl;
			break;
		}
		cout<<"\nPerform another operation? (Enter y for yes and n for no) : ";
		cin>>ans;
		cout<<"\n";
	}while(ans == 'y');
	return 0;
}
