//============================================================================
// Name        : A5-MST.cpp
// Author      : AJ
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

class MST{
private:
	vector < vector<int> > a; // 2D array
	int n; // Number of cities
	vector <string> city; // City name array
public:
	void getNumberOfCities(){
		cout<<"Enter the number of cities where your offices are located : ";
		cin>>n;
	}
	void init2DArray(){
		vector <int> temp;
		for(int i=0; i<n; i++){
			temp.push_back(0);
		}
		for(int i=0; i<n; i++){
			a.push_back(temp);
		}
	}
	void getCityName(){
		string s;
		cout<<"\nEnter the names of cities where your offices are located : "<<endl;
		for(int i=0; i<n; i++){
			cout<<"Enter name of city "<<i+1<<" - ";
			cin>>s;
			city.push_back(s);
		}
	}
	int searchCity(string cityName){
		for(int i=0; i<n; i++){
			if(cityName == city[i])
				return i;
		}
		return -1;
	}
	void get2DArray(){
		string s1, s2;
		int i1, i2;
		char ans;
		int cost;
		cout<<"\nEnter the phone line details : "<<endl;
		do{
			cout<<"Enter the name of two cities which can be connected via phone line : ";
			cin>>s1>>s2;
			cout<<"Enter the cost of phone line between these two cities : ";
			cin>>cost;
			i1 = searchCity(s1);
			i2 = searchCity(s2);
			if(i1!=-1 && i2!=-1){
				a[i1][i2] = cost;
				a[i2][i1] = cost;
			}
			else if(i1==-1 && i2==-1){
				cout<<"The cities entered are not present in the database. Please enter valid cities next time!!"<<endl;
			}
			else if(i1==-1 && i2!=-1){
				cout<<"The city "<<s1<<" is not present in the database. Please enter valid city next time!!"<<endl;
			}
			else if(i2==-1 && i1!=-1){
				cout<<"The city "<<s2<<" is not present in the database. Please enter valid city next time!!"<<endl;
			}
			else{
				cout<<"I don't know what the error is."<<endl;
			}
			cout<<"\nEnter details of another pair of cities? (Enter y for yes and n for no) : ";
			cin>>ans;
			cout<<"\n";
		}while(ans == 'y');
	}
	void display2DArray(){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cout<<a[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
	void PrimsAlgorithm(){
		vector <int> visited;
		queue <int> q;
		string s;
		for(int i=0; i<n; i++)
			visited.push_back(0);
		cout<<"Enter the city name from where you wish to start establishing phone lines : ";
		cin>>s;
		int index = searchCity(s);
		visited[index] = 1;
		int min;
		int pos = 0, weightSum = 0, i;
		int count = 1;
		q.push(index);
		while(count<n){
			min = INT_MAX;
			while(!q.empty()){
                i = q.front();
				for(int j=0; j<n; j++){
					if(a[i][j]!=0 && visited[j]!=1 && a[i][j]<=min){
						min = a[i][j];
						pos = j;
					}
				}
				q.pop();
			}
			visited[pos] = 1;
			weightSum += min;
			q.push(pos);
			for(int k=0; k<n; k++){
                if(visited[k]==1)
                    q.push(k);
			}
			count++;
		}
		cout<<"Weight of Minimum Spanning Tree is : "<<weightSum<<endl;
	}
};
int main() {
	MST ob;
	ob.getNumberOfCities();
	ob.init2DArray();
	ob.getCityName();
	ob.get2DArray();
	cout<<"\nDisplaying Adjacency Matrix : "<<endl;
	ob.display2DArray();
	ob.PrimsAlgorithm();
	return 0;
}
