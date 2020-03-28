//============================================================================
// Name        : A9-Set.cpp
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
	Node *next;
public:
	Node(){
		data = 0;
		next = NULL;
	}
	friend class Set;
};

class Set{
private:
	Node *root;
public:
	Set(){
		root = NULL;
	}
	Node* createNode(int data){
		Node *temp = new Node;
		temp->data = data;
		return temp;
	}
	void insertNode(int data){
		Node *p = createNode(data);
		if(root == NULL){
			root = p;
		}
		else{
			Node *q = root;
			if(p->data < q->data){
				p->next = q;
				root = p;
			}
			else{
				while(q!=NULL){
					if(p->data == q->data)
						break;
					q = q->next;
				}
				if(q!=NULL && p->data == q->data){
					cout<<p->data<<" already exists in the set."<<endl;
					delete p;
				}
				else{
					q = root;
					while(q->next!=NULL &&  (p->data > q->next->data))
						q = q->next;
					p->next = q->next;
					q->next = p;
				}
			}
		}
	}
	void deleteNode(int data){
		Node *p = root;
		Node *q = NULL;
		if(root->data == data){
			root = root->next;
			p->next = NULL;
			cout<<data<<" deleted from the set."<<endl;
			delete p;
		}
		else{
			p = p->next;
			while(p!=NULL){
				if(p->data == data){
					q->next = p->next;
					p->next = NULL;
					delete p;
					cout<<data<<" deleted from the set."<<endl;
					break;
				}
				q = p;
				p = p->next;
			}
			if(p == NULL)
				cout<<data<<"was not present in the set."<<endl;
		}
	}
	void sizeOfSet(){
		Node *p = root;
		int c=0;
		while(p!=NULL){
			c++;
			p = p->next;
		}
		cout<<c<<endl;
	}
	void intersection(Set &s1, Set &s2){
		root = NULL;
		Node *p = s1.root;
		Node *q = s2.root;
		while(p!=NULL && q!=NULL){
			if(p->data == q->data){
				insertNode(p->data);
				p = p->next;
				q = q->next;
			}
			else if(p->data < q->data)
				p = p->next;
			else
				q = q->next;
		}
	}
	void unionOfSets(Set &s1, Set &s2){
		root = NULL;
		Node *p = s1.root;
		Node *q = s2.root;
		while(p!=NULL && q!=NULL){
			if(p->data == q->data){
				insertNode(p->data);
				p = p->next;
				q = q->next;
			}
			else if(p->data < q->data){
				insertNode(p->data);
				p = p->next;
			}
			else{
				insertNode(q->data);
				q = q->next;
			}
		}
		while(p!=NULL){
			insertNode(p->data);
			p = p->next;
		}
		while(q!=NULL){
			insertNode(q->data);
			q = q->next;
		}
	}
	void differenceOfSets(Set &s1, Set &s2){
		root = NULL;
		Node *p = s1.root;
		Node *q = s2.root;
		while(p!=NULL){
			if(p->data != q->data){
				insertNode(p->data);
				p = p->next;
			}
			else{
				p = p->next;
				if(q->next!=NULL)
					q = q->next;
			}
		}
	}
	void subset(Set &s1, Set &s2){
		Node *p = s1.root;
		int ctr = 0;
		while(p!=NULL){
			if(search(s2, p->data)){
				p = p->next;
			}
			else{
				ctr = 1;
				break;
			}
		}
		if(ctr == 0){
			cout<<"The given set is a subset!"<<endl;
		}
		else{
			cout<<"The given set is not a subset."<<endl;
		}
	}
	int search(Set &s1, int data){
		Node *p = s1.root;
		while(p!=NULL){
			if(p->data == data)
				return 1;
			p = p->next;
		}
		return 0;
	}
	void display(){
		if(root){
			Node *p = root;
			cout<<"{";
			while(p->next!=NULL){
				cout<<p->data<<", ";
				p = p->next;
			}
			cout<<p->data<<"}"<<endl;
		}
		else
			cout<<"NULL set"<<endl;
	}
};

int main() {
	Set s1, s2, s3, s4, s5, s6, s7, s8;
	int choice, n;
	int data;
	int *inp;
	char ans;
	do{
		cout<<"Menu:\n1. Insert an element into the first set\n2. Insert an element into the second set\n3. Delete an element from first set\n4. Delete an element from second set\n5. Get the size of sets\n6. Display the sets\n7. Intersection of the two sets\n8. Union of the two sets\n9. Difference between the sets\n10. Check for a subset\nEnter your choice : ";
		cin>>choice;
		switch(choice){
		case 1:
			cout<<"\nEnter the element to be inserted into the first set : ";
			cin>>data;
			s1.insertNode(data);
			break;
		case 2:
			cout<<"\nEnter the element to be inserted into the second set : ";
			cin>>data;
			s2.insertNode(data);
			break;
		case 3:
			cout<<"\nEnter the element to be deleted from the first set : ";
			cin>>data;
			s1.deleteNode(data);
			break;
		case 4:
			cout<<"\nEnter the element to be deleted from the second set : ";
			cin>>data;
			s2.deleteNode(data);
			break;
		case 5:
			cout<<"The size of first set is : ";
			s1.sizeOfSet();
			cout<<"The size of second set is : ";
			s2.sizeOfSet();
			break;
		case 6:
			cout<<"The first set is : ";
			s1.display();
			cout<<"The second set is : ";
			s2.display();
			break;
		case 7:
			s3.intersection(s1, s2);
			cout<<"The intersection of the two sets is : ";
			s3.display();
			break;
		case 8:
			s4.unionOfSets(s1, s2);
			cout<<"The union of the two sets is : ";
			s4.display();
			break;
		case 9:
			s3.intersection(s1, s2);
			cout<<"Set 1 - Set 2 : ";
			s5.differenceOfSets(s1, s3);
			s5.display();
			cout<<"\n";
			cout<<"Set 2 - Set 1 : ";
			s6.differenceOfSets(s2, s3);
			s6.display();
			break;
		case 10:
			cout<<"Enter the number of elements in the subset : ";
			cin>>n;
			inp = new int[n];
			cout<<"Enter the elements of subset : ";
			for(int i=0; i<n; i++){
				cin>>inp[i];
				s7.insertNode(inp[i]);
			}
			cout<<"Comparing with first set : ";
			s8.subset(s7, s1);
			cout<<"\nComparing with second set : ";
			s8.subset(s7, s2);
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
