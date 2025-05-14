#pragma once
#include "/public/read.h"
#include <string>
#include <algorithm>
#include <numeric>
#include "item.h"
#include <map>

using namespace std;

// - - - Inventory BST class - - - //
class Inventory {
	map<string,Item> inventory_db;
	public:
	Inventory() = default;

	void insert(const Item& new_item) {
		inventory_db.insert({new_item.name, item});
	}
/*
		Node* root = nullptr;
		void insert(Node*& node, const Item& item) {
             if (!node) node = new Node(item);
             else if (item.name== node->item.name) node->item.count++;
             else if (item < node->item) insert(node->left, item);
             else insert(node->right, item);
         }*/

	bool contains(string name) {
		if (inventory_db.contains(name)) return true;
		else{
			return false;
		}
	}

	void erase(string name) {
		inventory_db.erase(name);
	}

	Item get_item(string name) {
		if (inventory_db.contains(name)) return inventory_db[name];
		else {
			throw runtime_error("item not found");
		}
	}
	/*
	   private:
	   struct Node {
	   Item item_in_Item_class;
	   Node *left, *right;
	   Node(const Item& new_item) : item(new_item), left(nullptr), right(nullptr) {}
	   };

	   Node* root = nullptr;
	   void insert(Node*& node const Item& item) {
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
	   }else if (name < node->item.name) return remove(node->lef    t, name);
	   else return remove(node->right, name);
	   }


	// - - - - - Map - - - - - // 
	map<string, Item> inventory;
	inventory.insert({item.key_item,{key_item,item.count, item.value}}); // insert function
	if (inventory.contains(item.key_item)) cout << "we have " << item.key_item << " in the inventory." << endl;

	public:
	void add(const Item& item) {insert(root, item);}
	bool drop(const string& name) {return remove(root, name); }
	void print_inventory() const {
	if(!root) cout << "Inventory is empty.\n";
	else print_in_order(root);
	}
	*/
};

