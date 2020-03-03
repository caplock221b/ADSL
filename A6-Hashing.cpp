//============================================================================
// Name        : A6-Hashing.cpp
// Author      : AJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Dictionary{
private:
	string word;
	string meaning;
public:
	Dictionary(){
		word = "";
		meaning = "";
	}
	friend class Hashing;
};

class Hashing{
private:
	Dictionary ob[26];
public:
	void insertWithoutReplacement(){
		int key, check;
		string w, m;
		cout<<"\tEnter the word to be inserted in the dictionary : ";
		cin>>w;
		cin.ignore();
		cout<<"\tEnter the meaning of the word : ";
		getline(cin, m);
		key = w[0]-97;
		check = key;
		if(ob[key].word == ""){
			ob[key].word = w;
			ob[key].meaning = m;
		}
		else{
			while(ob[key].word != ""){
				key = (key+1)%26;
				if(key==check)
					break;
			}
			if(key==check){
				cout<<"\tThe Dictionary is full. Further insertions cannot take place."<<endl;
			}
			else{
				ob[key].word = w;
				ob[key].meaning = m;
			}
		}
	}
	void insertWithReplacement(){
		int key, check;
		string w, m;
		cout<<"\tEnter the word to be inserted in the dictionary : ";
		cin>>w;
		cin.ignore();
		cout<<"\tEnter the meaning of the word : ";
		getline(cin, m);
		key = w[0]-97;
		check = key;
		if(ob[key].word == ""){
			ob[key].word = w;
			ob[key].meaning = m;
		}
		else{
			if(ob[key].word[0]!=w[0]){
				int k = key;
				int c = k;
				while(ob[k].word!=""){
					k = (k+1)%26;
					if(k==c)
						break;
				}
				if(k==c){
					cout<<"\tThe Dictionary is full. Further insertions cannot take place."<<endl;
				}
				else{
					ob[k].word = ob[key].word;
					ob[k].meaning = ob[key].meaning;
					ob[key].word = w;
					ob[key].meaning = m;
				}
			}
			else{
				while(ob[key].word!=""){
					key = (key+1)%26;
					if(key==check)
						break;
				}
				if(key==check)
					cout<<"\tThe Dictionary is full. Further insertions cannot take place."<<endl;
				else{
					ob[key].word = w;
					ob[key].meaning = m;
				}
			}
		}
	}
	void find(){
		string w;
		cout<<"\tEnter the word whose meaning you wish to find in the dictionary : ";
		cin>>w;
		int key = w[0]-97;
		int check = key;
		if(ob[key].word==w){
			cout<<"\tWord found at position "<<key<<" in the dictionary."<<endl;
			cout<<"\tIt's meaning is : "<<ob[key].meaning<<endl;
		}
		else{
			key = (key+1)%26;
			while(ob[key].word!=w){
				key = (key+1)%26;
				if(key==check)
					break;
			}
			if(key==check){
				cout<<"\tWord is not present in the dictionary."<<endl;
			}
			else{
				cout<<"\tWord found at position "<<key<<" in the dictionary."<<endl;
				cout<<"\tIt's meaning is : "<<ob[key].meaning<<endl;
			}
		}
	}
	void del(){
		string w;
		cout<<"\tEnter the word whose meaning you wish to delete from the dictionary : ";
		cin>>w;
		int key = w[0]-97;
		int check = key;
		if(ob[key].word==w){
			cout<<"\tWord found at position "<<key<<" in the dictionary."<<endl;
			ob[key].word = "";
			ob[key].meaning = "";
			cout<<"\tWord has been deleted."<<endl;
		}
		else{
			key = (key+1)%26;
			while(ob[key].word!=w){
				key = (key+1)%26;
				if(key==check)
					break;
			}
			if(key==check){
				cout<<"Word is not present in the dictionary."<<endl;
			}
			else{
				cout<<"\tWord found at position "<<key<<" in the dictionary."<<endl;
				ob[key].word = "";
				ob[key].meaning = "";
				cout<<"\tWord has been deleted."<<endl;
			}
		}
	}
	void display(){
		cout<<"\tWord\t\tMeaning"<<endl;
		for(int i=0; i<26; i++){
			if(ob[i].word != ""){
				cout<<"\t"<<ob[i].word<<"\t\t"<<ob[i].meaning<<endl;
			}
		}
	}
};
int main() {
	Hashing h;
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
				h.insertWithoutReplacement();
				break;
			case 2:
				h.find();
				break;
			case 3:
				h.del();
				break;
			case 4:
				h.display();
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
				h.insertWithReplacement();
				break;
			case 2:
				h.find();
				break;
			case 3:
				h.del();
				break;
			case 4:
				h.display();
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
