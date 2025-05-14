#pragma once
#include <iostream>
#include "Bridges.h"
#include "CircDLelement.h"
#include <string>

using namespace bridges;
using std::string;

// m was here

class Node {
	string name;
	Node *next = nullptr;
	Node *prev = nullptr;
	public:
	Node(const string &n_name) : name{n_name} {}
	void set_name(const string& n) {
		name = n;
	}
	void set_prev(Node* n) {
		prev = n;
	}
	void set_next(Node* n) {
		next = n;
	}
	Node* get_prev() const {
		return prev;
    }
    Node* get_next() const {
        return next;
    }
	string get_name() const {
		return name;
	}

};


class CircleList {
	Node* head = nullptr;
	int size = 0;
	public:
	CircleList(){}
	CircleList(Node* n) : head{n} {}

	void set_head(Node* n) {
		head = n;
	}

	Node* get_head() {
		return head;
	}
	//add a node into circular linked list
	void add_node(Node* n) {
		if (head == nullptr) {
			head = n;
			n->set_prev(n);
			n->set_next(n);
		} else if(size == 1) {
			head->set_next(n);
			head->set_prev(n);
			n->set_next(head);
			n->set_prev(head);
		} else {
			Node* temp = head->get_prev();
			temp->set_next(n);
			head->set_prev(n);
			n->set_next(head);
			n->set_prev(temp);
		}
		size++;
	}

	//add item into circular linked list with vector
	void add_node(const vector<string>& item_list) {
		for (const string& item : item_list) {
			Node* n = new Node(item);
			add_node(n);
		}
	}

	Node* get_node(const string& str) {
		Node* temp = head;
		while(temp) {
			if(temp->get_name() == str) {
				return temp;
			} else {
				temp = temp->get_next();
			}
		}
		return nullptr; //if node is not in list
	}
	
	void delete_node(const string& str) {
		Node* del_node = get_node(str);
		if (del_node) { //if del_node is not nullptr
			
			if (size > 1) {//rearange list
				Node* prev_node = del_node->get_prev();
				Node* next_node = del_node->get_next();
				prev_node->set_next(next_node);
				next_node->set_prev(prev_node);
			}

			//if node deleted is head, change head to next node
			if (del_node->get_name() == head->get_name()) {
				head = del_node->get_next();
			}
		delete del_node;
		size--;
		}
	}
	
	void print() {
		if (head != nullptr) {
			Node* temp = head;
			do {
				cout << temp->get_name() << endl;
				temp = temp->get_next();
			} while (temp != head);
		}
	}

	//add elements to circle list for bridge
	void add_element(CircDLelement<string>* first_node, CircDLelement<string>* node) {
        	auto prev_node = first_node->getPrev();
			
			if (prev_node != first_node) {
				prev_node->setNext(node);
				first_node->setPrev(node);
				node->setPrev(prev_node);
				node->setNext(first_node);
			} else {
				first_node->setNext(node);
				first_node->setPrev(node);
				node->setNext(first_node);
				node->setPrev(first_node);
			}

	}

	// visualize bridge circle linked list
	void visualize_list(const vector<string>& item_list) {
		Bridges bridges (3, "JunKuang",
				"267242104525");

		vector<CircDLelement<string>*> node_vec;

		CircDLelement<string> *first_node = new CircDLelement<string>(item_list.at(0), item_list.at(0));
		first_node->setPrev(first_node);
		first_node->setNext(first_node);
		node_vec.push_back(first_node);

		CircDLelement_List<string> circle_list(first_node);

		for (int i = 1; i < item_list.size(); i++) {
			const string& str = item_list.at(i);
			CircDLelement<string> *node = new CircDLelement<string>(str, str);
			node_vec.push_back(node);

			add_element(first_node,node);
		}
		bridges.setDataStructure(first_node);
		bridges.visualize();

		for (auto ptr : node_vec) {
			delete ptr;
		}

	}

	~CircleList() {
		if (head) {
			Node* temp = head->get_next();
			while(temp != head) {
				Node* temp2 = temp;
				temp = temp->get_next();
				delete temp2;
			}
		delete head;
		head = nullptr;
		size = 0;
		}
	}

};


//add elements to circle list for bridge
void add_element(CircDLelement<string>* first_node, CircDLelement<string>* node) {
	auto prev_node = first_node->getPrev();

	if (prev_node != first_node) { //when their is more than one node in list
		prev_node->setNext(node);
		first_node->setPrev(node);
		node->setPrev(prev_node);
		node->setNext(first_node);
	} else {
		first_node->setNext(node);
		first_node->setPrev(node);
		node->setNext(first_node);
		node->setPrev(first_node);
	}

}

// visualize bridge circle linked list
void visualize_list(const vector<string>& item_list) {
	Bridges bridges (3, "JunKuang",
			"267242104525");
	
	// hold vector of pointer to delete, to stop memory leak
	vector<CircDLelement<string>*> node_vec;
	
	//initialize the list or it does not work
	CircDLelement<string> *first_node = new CircDLelement<string>(item_list.at(0), item_list.at(0));
	first_node->setPrev(first_node);
	first_node->setNext(first_node);
	node_vec.push_back(first_node);

	CircDLelement_List<string> circle_list(first_node);

	//adds node to the circle list
	for (int i = 1; i < item_list.size(); i++) {
		const string& str = item_list.at(i);
		CircDLelement<string> *node = new CircDLelement<string>(str, str);
		node_vec.push_back(node);

		add_element(first_node,node);
	}
	bridges.setDataStructure(first_node);
	bridges.visualize();

	for (auto ptr : node_vec) {
		delete ptr;
	}
}


//this one shows who's turn it is now and the person going next on Bridge
//the person going right now is has a green circle
//the person going next has a red circle
//this take in a vector of class
//the class need to have get_name() and get_turn()
//get_turn() should return int, that tells who going next
template<typename T>
void visualize(T& list) {
	//checking if there is something in list
	if (list.size() >= 1) {
		Bridges bridges (3, "JunKuang",
				"267242104525");

		// hold vector of pointer to delete, to stop memory leak
		vector<CircDLelement<string>*> node_vec;

		//current person turn
		auto curr = list.at(0);
		CircDLelement<string> *curr_el{};
		//next person turn
		auto next = list.at(0);
		CircDLelement<string> *next_el{};

		//initialize the list or it does not work
		CircDLelement<string> *first_node = new CircDLelement<string>(list.at(0)->get_name(), list.at(0)->get_name());
		first_node->setPrev(first_node);
		first_node->setNext(first_node);
		node_vec.push_back(first_node);
		
		curr_el = next_el = first_node;

		CircDLelement_List<string> circle_list(first_node);

		//adds node to the circle list
		for (int i = 1; i < list.size(); i++) {
			auto item = list.at(i);
			string str = item->get_name();
			CircDLelement<string> *node = new CircDLelement<string>(str, str);
			node_vec.push_back(node);
			
			//finds the current and next person turn
			if (item->get_turn() < curr->get_turn()) {
				next = curr;
				next_el = curr_el;
				curr = item;
				curr_el = node;
			} else if (item->get_turn() < next->get_turn()) { //finds who is going next
				next = item;
				next_el = node;
			}

			add_element(first_node,node);
		}

		curr_el->setColor("green");
		next_el->setColor("red");

		bridges.setDataStructure(first_node);
		bridges.visualize();

		for (auto ptr : node_vec) {
			delete ptr;
		}

	}
}






