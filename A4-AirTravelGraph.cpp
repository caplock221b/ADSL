//============================================================================
// Name        : A4-AirTravelGraph.cpp
// Author      : AJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
 	There are flight paths between cities. If there is a flight between city A and city B
	then there is an edge between the cities. The cost of the edge can be the time that
	flight takes to reach city B from A, or the amount of fuel used for the journey.
	Represent this as a graph. The node can be represented by airport name or name
	of the city. Use adjacency list representation of the graph. (Operation to be
	performed adding and deleting edge, adding and deleting vertices, calculated in-
	degree and out-degree for directed graph. Use any traversal to traverse graph)
*/
#include <iostream>
using namespace std;

class Node{
private:
	string cityName;
	int travelTime;
	Node *right;
	Node *down;
public:
	Node(string cityName, int travelTime = 0){
		this->cityName = cityName;
		this->travelTime = travelTime;
		right = down = NULL;
	}
	friend class AirTravel;
};

class AirTravel{
private:
	Node *start;
public:
	AirTravel(){
		start = NULL;
	}
	void createGraph(){
		string cityName="", tName="";
		int t;
		char ch;
		cout<<"Enter city name : ";
		cin>>cityName;
		cin.ignore(256, '\n');
		Node *city = new Node(cityName);
		Node *last = NULL;
		if(start == NULL){
			start = last = city;
		}
		else{
			last = start;
			while(last->down!=NULL)
				last = last->down;
			last->down = city;
			last = last->down;
		}
		do{
			Node *temp = NULL;
			cout<<"Enter name of a city which is connected to "<<city->cityName<<" : ";
			cin>>tName;
			cin.ignore(256, '\n');
			cout<<"Enter the time of flight from "<<city->cityName<<" to "<<tName<<" : ";
			cin>>t;
			cin.ignore(256, '\n');
			temp = new Node(tName, t);
			last->right = temp;
			last = temp;
			cout<<"Add another city which is connected to "<<city->cityName<<"? (Enter y for yes and n for no) : ";
			cin>>ch;
			cout<<"\n";
		}while(ch == 'y');
	}
	void display(){
		Node *p = start;
		Node *last = start;
		while(last!=NULL){
			cout<<"\tFlights from "<<(last->cityName)<<" :"<<endl;
			cout<<"\t\tTo City\t\tTravel Time"<<endl;
			last = last->right;
			while(last!=NULL){
				cout<<"\t\t"<<(last->cityName)<<"\t\t"<<(last->travelTime)<<" hours"<<endl;
				last = last->right;
			}
			cout<<"\n";
			p = p->down;
			last = p;
		}
	}
	Node* findANode(string city){
		Node *p = start;
		while(p->cityName!=city)
			p = p->down;
		if(p!=NULL)
            return p;
        else
            return NULL;
	}
	void addEdge(){
		string fromCity, toCity;
		int t;
		cout<<"Add an edge from which city : ";
		cin>>fromCity;
		cout<<"Add edge from "<<fromCity<<" to which city : ";
		cin>>toCity;
		cout<<"Enter the time of flight from "<<fromCity<<" to "<<toCity<<" : ";
		cin>>t;
		Node *p = findANode(fromCity);
		Node *q = new Node(toCity, t);
		while(p->right!=NULL){
			p = p->right;
		}
		p->right = q;
	}
	void deleteEdge(){
		string fromCity, toCity;
		cout<<"Delete an edge from which city : ";
		cin>>fromCity;
		cout<<"Delete edge from "<<fromCity<<" to which city : ";
		cin>>toCity;
		Node *p = findANode(fromCity);
		Node *q = NULL;
		while(p->cityName!=toCity){
			q = p;
			p = p->right;
		}
		q->right = p->right;
		p->right = NULL;
		delete p;
		cout<<"Flight Information from "<<fromCity<<" to "<<toCity<<" has been deleted."<<endl;
	}
	void deleteVertex(){
		string city;
		cout<<"Which city's travel information do you wish to delete? : ";
		cin>>city;
		Node *p = start;
		Node *q = NULL;
		while(p->cityName!=city){
			q = p;
			p = p->down;
		}
		if(p == start)
			start = start->down;
		else
			q->down = p->down;
		q = p->right;
		while(q!=NULL){
			delete p;
			p = q;
			q = q->right;
		}
		cout<<"Flight Information of "<<city<<" has been deleted."<<endl;
	}
	void outDegree(){
		string city;
		cout<<"Enter the name of city whose out degree you wish to find : ";
		cin>>city;
		Node *p = findANode(city);
		if(p!=NULL){
            int c = 0;
            p = p->right;
            while(p!=NULL){
                c++;
                p = p->right;
            }
            cout<<"The number of flights from "<<city<<" is "<<c<<"."<<endl;
		}
		else
            cout<<"The flight information for "<<city<<" does not exist."<<endl;
	}
	void inDegree(){
		string city;
		cout<<"Enter the name of city whose in degree you wish to find : ";
		cin>>city;
		cin.ignore();
		int c = 0;
		Node *p = start;
		Node *last = NULL;
		while(p!=NULL){
            last = p->right;
			if(p->cityName != city){
				while(last!=NULL){
					if(last->cityName == city)
						c++;
					last = last->right;
				}
			}
			p = p->down;
		}
		cout<<"The number of flights to "<<city<<" is "<<c<<"."<<endl;
	}
};
int main() {
	AirTravel ob;
	char ans;
	int choice;
	do{
		cout<<"Menu :\n1. Insert flight information of a new city\n2. Display the flight timings\n3. Add a flight route to a specified city\n4. Delete flight route from a specified city\n5. Delete flight information of a specified city\n6. Find the number of flights leaving a specified city\n7. Find the number of flights reaching a specified city\nEnter your choice 1, 2, 3, 4, 5, 6 or 7 : ";
		cin>>choice;
		switch(choice){
		case 1:
			ob.createGraph();
			break;
		case  2:
			ob.display();
			break;
		case 3:
			ob.addEdge();
			break;
		case 4:
			ob.deleteEdge();
			break;
		case 5:
			ob.deleteVertex();
			break;
		case 6:
			ob.outDegree();
			break;
		case 7:
			ob.inDegree();
			break;
		default:
			cout<<"Invalid choice! Please enter valid choice next time."<<endl;
			break;
		}
		cout<<"Perform another operation? (Enter y for yes and n for no) : ";
		cin>>ans;
		cout<<"\n";
	}while(ans == 'y');
	return 0;
}
