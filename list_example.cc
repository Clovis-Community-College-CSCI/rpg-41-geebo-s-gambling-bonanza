#include<iostream>
#include<string>
#include"list.h"

class temp {
	string name;
	int turn = 0;
	public:
	temp(const string &n, int t) : name(n), turn(t) {}
	string get_name() {
		return name;
	}
	int get_turn() {
		return turn;
	}
};

int main() {
	// all you need to run my code to visualize is a vector of string
	//vector<string> name_list = {"cat", "dog", "fish", "tiger", "hi", "apple", "big"};
	

	vector<temp*> temp_list;
	for (int i = 1; i < 10; i++) {
		string name = "hi_" + to_string(i);
		temp* t = new temp(name,i);
		temp_list.push_back(t);
	}
	
	temp* t = new temp("first",0);
	temp_list.push_back(t);
	t = new temp("hello", 1);
	temp_list.push_back(t);


	// this would take vector and visualize on bridge
	//visualize_list(name_list);
	visualize(temp_list);

	for (auto t : temp_list) {
		delete t;
	}
	

}
