//============================================================================
// Name        : A2-Dictionary.cpp
// Author      : AJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
	A Dictionary stores keywords & its meanings. Provide facility for adding new
	keywords, deleting keywords, updating values of any entry, assign a given tree
	into another tree (=). Provide facility to display whole data sorted in ascending/
	Descending order. Also find how many maximum comparisons may require for
	finding any keyword. Use Binary Search Tree for implementation.
*/
#include <iostream>
#include <string.h>
using namespace std;

class Node{
private:
	string data;
	string meaning;
	Node *left;
	Node *right;
public:
	Node(string data, string meaning){
		this->data = data;
		this->meaning = meaning;
		left = NULL;
		right = NULL;
	}
	friend class Dictionary;
};

class Dictionary{
private:
	Node *root;
public:
	Dictionary(){
		root = NULL;
	}
	void insertEntryIntoDictionary(string data, string meaning){
		Node *p = new Node(data, meaning);
		if(root == NULL)
			root = p;
		else{
			Node *q = root;
			int flag = 0;
			while(flag == 0){
				if(p->data.compare(q->data) < 0){
					if(q->left != NULL)
						q = q->left;
					else{
						q->left = p;
						flag = 1;
					}
				}
				else if(p->data.compare(q->data) > 0){
					if(q->right != NULL)
						q = q->right;
					else{
						q->right = p;
						flag = 1;
					}
				}
				else{
					flag = 1;
					delete p;
					cout<<"Entered data already exists in the Dictionary."<<endl;
				}
			}
		}
	}
	void inorderTraversal(Node *p){
		if(p!=NULL){
			inorderTraversal(p->left);
			cout<<p->data<<" - "<<p->meaning<<endl;
			inorderTraversal(p->right);
		}
	}
	void ascendingOrderDisplay(){
		cout<<"The contents of the Dictionary in ascending order are :"<<endl;
		inorderTraversal(root);
	}
	void reverseInorderTraversal(Node *p){
		if(p!=NULL){
			reverseInorderTraversal(p->right);
			cout<<p->data<<" - "<<p->meaning<<endl;
			reverseInorderTraversal(p->left);
		}
	}
	void descendingOrderDisplay(){
		cout<<"The contents of the Dictionary in descending order are :"<<endl;
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
			if(p->data.compare(data) == 0){
				cout<<"Search Successful! Data is present as an entry in the Dictionary."<<endl;
				cout<<"Total number of comparisons : "<<comparisons<<endl;
				flag = 1;
			}
			else if(p->data.compare(data) > 0){
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
	void deleteEntry(){
		string data;
		cout<<"Enter the data of entry to be deleted : ";
		cin>>data;
		Node *p = root;
		Node *q = NULL;
		int flag = 0;
		while(flag == 0){
			if(p->data.compare(data) == 0){
				flag = 1;
			}
			else if(p->data.compare(data) > 0){
				if(p->left != NULL){
					q = p;
					p = p->left;
				}
				else{
					cout<<"Data not present as an entry in the Dictionary."<<endl;
					flag = 1;
				}
			}
			else{
				if(p->right != NULL){
					q = p;
					p = p->right;
				}
				else{
					cout<<"Data not present as an entry in the Dictionary."<<endl;
					flag = 1;
				}
			}
		}
		if(p->data.compare(data) == 0){
			if(p->left==NULL && p->right==NULL){ // If data is present on a leaf node
				if(q->left == p)
					q->left = NULL;
				else
					q->right = NULL;
				delete p;
			}
			else{ // If data is present on intermediate node
				if(p->right!=NULL){
					Node *t = p->right;
					Node *s = p;
					while(t->left!=NULL){
						s = t;
						t = t->left;
					}
					p->data = t->data;
					p->meaning = t->meaning;
					if(s->left == t)
						s->left = t->right;
					else
						s->right = t->right;
					delete t;
				}
				else{
					if(q==NULL){ // If data is present on root node
						q = p;
						p = p->left;
						root = p;
						delete q;
					}
					else{ // If data is not present on root node
						if(q->left == p){
							q->left = p->left;
							delete p;
						}
						else{
							q->right = p->left;
							delete p;
						}
					}
				}
			}
		}
		if(root != NULL)
			ascendingOrderDisplay();
		else
			cout<<"The Dictionary is empty!"<<endl;
	}
	void updateMeaningOfaWord(){
		string d;
		cout<<"Enter the word whose meaning you wish to update : ";
		cin>>d;
		Node *p = root;
		int flag = 0;
		int found = 0;
		while(flag == 0){
			if(p->data.compare(d) == 0){
				found = 1;
				flag = 1;
			}
			else if(p->data.compare(d) > 0){
				if(p->left != NULL)
					p = p->left;
				else{
					found = 0;
					flag = 1;
				}
			}
			else{
				if(p->right != NULL)
					p = p->right;
				else{
					found = 0;
					flag = 1;
				}
			}
		}
		if(found == 1){
			string m;
			cin.ignore();
			cout<<"Enter the new meaning of the word : ";
			getline(cin, m);
			p->meaning = m;
		}
		else
			cout<<"The word is not present in the dictionary."<<endl;
	}
};

int main() {
	Dictionary ob;
	int choice;
	char c;
	string data = "";
	string meaning = "";
	do{
		cout<<"Menu :\n1. Insert an entry into the Dictionary\n2. Display the contents of the Dictionary\n3. Search for an entry in the Dictionary\n4. Delete an entry from the Dictionary\n5. Update the meaning of a word\nEnter your choice 1, 2, 3, 4 or 5 : ";
		cin>>choice;
		switch(choice){
		case 1:
			cout<<"Enter data to be inserted into the Dictionary : ";
			cin>>data;
			cin.ignore();
			cout<<"Enter its meaning : ";
			getline(cin, meaning);
			ob.insertEntryIntoDictionary(data, meaning);
			break;
		case 2:
			cout<<"\t1. Display in ascending order\n\t2. Display in descending order\nEnter your choice 1 or 2 : ";
			cin>>choice;
			switch(choice){
			case  1:
				ob.ascendingOrderDisplay();
				break;
			case 2:
				ob.descendingOrderDisplay();
				break;
			}
			break;
		case 3:
			ob.searchEntry();
			break;
		case 4:
			ob.deleteEntry();
			break;
		case 5:
			ob.updateMeaningOfaWord();
			break;
		default:
			cout<<"Please enter valid choice next time."<<endl;
			break;
		}
		cout<<"\nPerform another operation ? (Enter y for yes OR n for no) : ";
		cin>>c;
		cout<<"\n";
	}while(c == 'y');
	return 0;
}
