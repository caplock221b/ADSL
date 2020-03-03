//============================================================================
// Name        : A3-TBT.cpp
// Author      : AJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Node{
private:
	int data;
	Node *left, *right;
	int lflag, rflag;
public:
	Node(int data){
		this->data = data;
		left = right = NULL;
		lflag = rflag = 0;
	}
	friend class TBT;
};

class TBT{
private:
	Node *root;
	Node *dummy;
public:
	TBT(){
		root = NULL;
		dummy = NULL;
	}
	void createTBT(){
		int data;
		cout<<"Enter data : ";
		cin>>data;
		Node *p = new Node(data);
		if(root == NULL){
			dummy = new Node(0);
			root = p;
			dummy->left = dummy->right = root;
			root->left = root->right = dummy;
			root->lflag = root->rflag = 1;
		}
		else{
			Node *q = root;
			int flag = 0;
			while(flag == 0){
				if(p->data<q->data){
					if(q->lflag == 1){
						p->left = q->left;
						q->left = p;
						q->lflag = 0;
						p->lflag = 1;
						p->right = q;
						p->rflag = 1;
						flag = 1;
					}
					else
						q = q->left;
				}
				else{
					if(q->rflag == 1){
						p->right = q->right;
						q->right = p;
						p->rflag = 1;
						q->rflag = 0;
						p->left = q;
						p->lflag = 1;
						flag = 1;
					}
					else
						q = q->right;
				}
			}
		}
	}
	void inorderTraversal(){
		Node *temp = root;
		while(temp->lflag!=1){
			temp = temp->left;
		}
		while(temp!=dummy){
			cout<<temp->data<<" ";
			if(temp->rflag == 1){
				temp = temp->right;
			}
			else{
				temp = temp->right;
				while(temp->lflag!=1){
					temp = temp->left;
				}
			}
		}
		cout<<endl;
	}
};
int main(){
    TBT ob;
    char ans;
    int data, choice;
    do{
        cout<<"Menu :\n1. Insert a node in the threaded binary tree\n2. Display the threaded binary tree\nEnter your choice 1 or 2 : ";
        cin>>choice;
        switch(choice){
        case 1:
        	ob.createTBT();
        	break;
        case 2:
        	ob.inorderTraversal();
        	break;
        default:
            cout<<"Please enter valid choice next time."<<endl;
            break;
        }
        cout<<"Perform another operation? (Enter y for yes or n for no) : ";
        cin>>ans;
        cout<<"\n";
    }while(ans == 'y');
    return 0;
}
