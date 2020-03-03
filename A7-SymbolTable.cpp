//============================================================================
// Name        : A7-SymbolTable.cpp
// Author      : AJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Row{
private:
	string symbol;
	string attribute;
	int chain;
public:
	Row(){
		symbol = "";
		attribute = "";
		chain = -1;
	}
	friend class SymbolTable;
};

class SymbolTable{
private:
	Row a[26];
public:
	void insertWithoutReplacement(){
		int key, check, k;
		string sym, attr;
		cout<<"\tEnter a symbol : ";
		cin>>sym;
		cin.ignore();
		cout<<"\tEnter it's attribute : ";
		getline(cin, attr);
		key = sym[0]-97;
		k = key;
		check = key;
		if(a[key].symbol == ""){
			a[key].symbol = sym;
			a[key].attribute = attr;
		}
		else{
			if(a[key].symbol[0] != sym[0]){
				while(a[key].symbol != ""){
					if(a[key].symbol[0] == sym[0]){
						k = key;
					}
					key = (key+1)%26;
					if(key == check)
						break;
				}
				if(key == check)
					cout<<"The Symbol Table is full. No further insertions can take place."<<endl;
				else{
					if(k == check){
						a[key].symbol = sym;
						a[key].attribute = attr;
					}
					else{
						a[key].symbol = sym;
						a[key].attribute = attr;
						a[k].chain = key;
					}
				}
			}
			else{
				if(a[key].chain == -1){
					k = key;
					while(a[k].symbol != ""){
						k = (k+1)%26;
						if(check == k)
							break;
					}
					if(k == check)
						cout<<"The Symbol Table is full. No further insertions can take place."<<endl;
					else{
						a[k].symbol = sym;
						a[k].attribute = attr;
						a[key].chain = k;
					}
				}
				else{
					while(a[key].chain != -1){
						key = a[key].chain;
					}
					k = key;
					k = (k+1)%26;
					while(a[k].symbol != ""){
						k = (k+1)%26;
						if(check == k)
							break;
					}
					if(k == check)
						cout<<"The Symbol Table is full. No further insertions can take place."<<endl;
					else{
						a[k].symbol = sym;
						a[k].attribute = attr;
						a[key].chain = k;
					}
				}
			}
		}
	}
	void insertWithReplacement(){
		int key, check, k;
		string sym, attr;
		cout<<"\tEnter a symbol : ";
		cin>>sym;
		cin.ignore();
		cout<<"\tEnter it's attribute : ";
		getline(cin, attr);
		key = sym[0]-97;
		k = key;
		check = key;
		if(a[key].symbol == ""){
			a[key].symbol = sym;
			a[key].attribute = attr;
		}
		else{
			if(a[key].symbol[0] != sym[0]){
				int i;
				for(i=0; i<26; i++){
					if(a[i].chain == key)
						break;
				}
				k = key;
				while(a[k].symbol != ""){
					k = (k+1)%26;
					if(k == check)
						break;
				}
				if(k == check)
					cout<<"The Symbol Table is full. No further insertions can take place."<<endl;
				else{
					a[k].symbol = a[key].symbol;
					a[k].attribute = a[key].attribute;
					a[k].chain = a[key].chain;
					a[key].symbol = sym;
					a[key].attribute = attr;
					a[key].chain = -1;
					a[i].chain = k;
				}
			}
			else{
				if(a[key].chain == -1){
					k = key;
					while(a[k].symbol != ""){
						k = (k+1)%26;
						if(check == k)
							break;
					}
					if(k == check)
						cout<<"The Symbol Table is full. No further insertions can take place."<<endl;
					else{
						a[k].symbol = sym;
						a[k].attribute = attr;
						a[key].chain = k;
					}
				}
				else{
					while(a[key].chain != -1){
						key = a[key].chain;
					}
					k = key;
					k = (k+1)%26;
					while(a[k].symbol != ""){
						k = (k+1)%26;
						if(check == k)
							break;
					}
					if(k == check)
						cout<<"The Symbol Table is full. No further insertions can take place."<<endl;
					else{
						a[k].symbol = sym;
						a[k].attribute = attr;
						a[key].chain = k;
					}
				}
			}
		}
	}
	void findWithoutReplacement(){
		string sym;
		cout<<"\tEnter the symbol which you wish to find in the Symbol Table : ";
		cin>>sym;
		int key = sym[0]-97;
		int check = key;
		if(a[key].symbol == sym){
			cout<<"\tSymbol found at position "<<key<<endl;
			cout<<"\tName : "<<a[key].symbol<<"\tAttribute : "<<a[key].attribute<<endl;
			while(a[key].chain != -1){
				key = a[key].chain;
				cout<<"\tSymbol found at position "<<key<<endl;
				cout<<"\tName : "<<a[key].symbol<<"\tAttribute : "<<a[key].attribute<<endl;
			}
		}
		else{
			while(a[key].symbol != sym){
				key = (key+1)%26;
				if(key == check)
					break;
			}
			if(key == check)
				cout<<"\tThe given symbol does not exist!"<<endl;
			else{
				cout<<"\tSymbol found at position "<<key<<endl;
				cout<<"\tName : "<<a[key].symbol<<"\tAttribute : "<<a[key].attribute<<endl;
				while(a[key].chain != -1){
					key = a[key].chain;
					cout<<"\tSymbol found at position "<<key<<endl;
					cout<<"\tName : "<<a[key].symbol<<"\tAttribute : "<<a[key].attribute<<endl;
				}
			}
		}
	}
	void findWithReplacement(){
		string sym;
		cout<<"\tEnter the symbol which you wish to find in the Symbol Table : ";
		cin>>sym;
		int key = sym[0]-97;
		if(a[key].symbol == sym){
			cout<<"\tSymbol found at position "<<key<<endl;
			cout<<"\tName : "<<a[key].symbol<<"\tAttribute : "<<a[key].attribute<<endl;
			while(a[key].chain != -1){
				key = a[key].chain;
				cout<<"\tSymbol found at position "<<key<<endl;
				cout<<"\tName : "<<a[key].symbol<<"\tAttribute : "<<a[key].attribute<<endl;
			}
		}
		else
			cout<<"\tThe given symbol does not exist!"<<endl;
	}
	void delWithoutReplacement(){
        string sym;
	    cout<<"\tEnter the symbol to be deleted : ";
	    cin>>sym;
	    int key = sym[0]-97;
	    int check = key;
	    int prevKey = -1;
	    if(a[key].symbol == sym){
            a[key].symbol = "";
            a[key].attribute = "";
	    }
	    else{
            key = (key+1)%26;
            while(a[key].symbol[0] != sym[0]){
                key = (key+1)%26;
                if(key == check)
                    break;
            }
            if(key == check)
                cout<<"\tThe given symbol does not exist in the Symbol Table."<<endl;
            else{
                prevKey = key;
                if(a[key].symbol == sym){
                    a[key].symbol = "";
                    a[key].attribute = "";
                    a[prevKey].chain = a[key].chain;
                }
                else{
                    while(a[key].chain != -1){
                        prevKey = key;
                        key = a[key].chain;
                        if(a[key].symbol == sym)
                            break;
                    }
                    if(a[key].symbol == sym){
                        a[prevKey].chain = a[key].chain;
                        a[key].symbol = "";
                        a[key].attribute = "";
                    }
                }
            }
	    }
	}
	void delWithReplacement(){
	    string sym;
	    cout<<"\tEnter the symbol to be deleted : ";
	    cin>>sym;
	    int key = sym[0]-97;
	    int prevKey = -1;
	    if(a[key].symbol == sym){
            a[key].symbol = "";
            a[key].attribute = "";
            // Don't delete the chain
	    }
	    else{
            while(a[key].chain != -1){
                prevKey = key;
                key = a[key].chain;
                if(a[key].symbol == sym)
                    break;
            }
            if(prevKey != -1){
                a[prevKey].chain = a[key].chain;
                a[key].symbol = "";
                a[key].attribute = "";
            }
	    }
	}
	void display(){
		cout<<"\tIndex\tSymbol\tAttribute\tChain"<<endl;
		for(int i=0; i<26; i++){
			if(a[i].symbol != ""){
				cout<<"\t"<<i<<"\t"<<a[i].symbol<<"\t\t"<<a[i].attribute<<"\t"<<a[i].chain<<endl;
			}
		}
	}
};
int main() {
	SymbolTable s;
	char c;
	int choice;
	cout<<"Menu:\n1. Insertions without replacement\n2. Insertions with replacement\nEnter your choice 1 or 2 : ";
	cin>>choice;
	switch(choice){
	case 1:
		do{
			cout<<"\n\tMenu :\n\t1. Insert\n\t2. Find\n\t3. Delete\n\t4. Display\n\tEnter your choice : ";
			cin>>choice;
			switch(choice){
			case 1:
				s.insertWithoutReplacement();
				break;
			case 2:
				s.findWithoutReplacement();
				break;
			case 3:
				s.delWithoutReplacement();
				break;
			case 4:
				s.display();
				break;
			default:
				cout<<"\tPlease enter valid choice next time."<<endl;
				break;
			}
			cout<<"\n\tPerform another operation? Enter y for yes and n for no : ";
			cin>>c;
			cout<<"\n";
		}while(c=='y');
		break;
	case 2:
		do{
			cout<<"\n\tMenu :\n\t1. Insert\n\t2. Find\n\t3. Delete\n\t4. Display\n\tEnter your choice : ";
			cin>>choice;
			switch(choice){
			case 1:
				s.insertWithReplacement();
				break;
			case 2:
				s.findWithReplacement();
				break;
			case 3:
				s.delWithReplacement();
				break;
			case 4:
				s.display();
				break;
			default:
				cout<<"\tPlease enter valid choice next time."<<endl;
				break;
			}
			cout<<"\n\tPerform another operation? Enter y for yes and n for no : ";
			cin>>c;
			cout<<"\n";
		}while(c=='y');
		break;
	default:
		cout<<"Please enter valid choice next time."<<endl;
		break;
	}
	return 0;
}
