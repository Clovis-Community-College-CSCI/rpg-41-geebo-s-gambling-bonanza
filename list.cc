#include <iostream>
#include "Bridges.h"
#include "CircDLelement.h"
#include <string>

using namespace bridges;
using std::string;

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

void add_to(CircDLelement_List<string> &list, string new_name) {
    auto head = list.begin();
    auto tail = head--;

    cout << *head << endl;
    cout << *tail << endl;

//  CircDLelement<string>  *node = new CircDLelement<string> (new_name, new_name);

}


int main() {
	vector<string> name_list = {"cat", "dog", "fish", "tiger", "hi", "apple"};
	
	CircleList dl{};
	
	dl.visualize_list(name_list);

}
