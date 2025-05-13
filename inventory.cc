#include "/public/read.h"
#include <string>

using namespace std;

class Item {
	private: 
		string name = "Unknown";
		int value = 0;
		bool key_item = false;
		int count = 1;

	public:
		
	//	int healing = 0; would we even need this
	//	int damage = 0;

		Item() = default;
		Item(string new_name, int new_value, bool new_key): name(new_name), value(new_value), key_item(new_key) {}
	
	 bool get_key() const {
         return ket_item;
     }

	 string get_name() const {
         return name;
     }

		bool operator<(const Item& other) const {
			return name < other.name;
		}

	bool operator==(const Item& other) const {
		return name == other.name;
	}

		friend ostream& operator<<(ostream& outs, const Item& item) {return outs << item.get_name();
		}
};

class Inventory_BST {
	private:
		struct Node {
			Item item;
			Node *left, *right;
			Node(const Item& new_item): item(new_item), left(nullptr), right(nullptr) {}
		};
		Node* root = nullptr;
		
		void insert(Node*& node, const Item& item) {
			if (!node) node = new Node(item);
			else if (item.name== node->item.name) node->item.count++;
			else if (item < node->item) insert(node->left, item);
			else insert(node->right, item);
		}

		void print_in_order(Node* node) const {
			if (!node) return;
			print_in_order(node->left);
			cout << node->item << '\n';
			print_in_order(node->right);
		}

		bool remove(Node*& node, const string& name){
			if (!node) return false;
			if (name == node->item.name){
				if (node->item.key_item) return false; //when there is a key item, can't drop it.
				if (--node->item.count > 0) return true; // delete the node
				Node* temp = nullptr;
				if (!node->left) {
					temp = node;
					node = node->right;
				} else if (!node->right) {
					temp = node;
					node = node->left;
				} else {
					Node * pred = node->left;
					while (pred->right) pred = pred->right;
					node->item = pred->item;
					remove(node->left, pred->item.name);
					return true;
					delete temp;
					return true;
				}else if (name < node->item.name) return remove(node->left, name);
				else return remove(node->right, name);
			}
			public:
			void add(const Item& item) {insert(root, item);}
			bool drop(const string& name) {return remove(root, name); }
			void print_inventory() const {
				if(!root) cout << "Inventory is empty.\n";
				else print_in_order(root);
			}
		};
