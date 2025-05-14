#pragma once
#include "/public/read.h"
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;
// item.h

// - - - Item Class - - - //

class Item {
	private:
		string name = "Unknown";
		int value = 0;
		bool key_item = false; // README instructions wanted a key item --> do those go with BST?
		int count = 1;

	public:
		Item() = default; //Kerney taught this in class --> keeps the "free stuff?"
		Item(string new_name, int new_value, bool new_key, int new_count): name(new_name), value(new_value), key_item(new_key), count(new_count) {}

	// Getters
		string get_name() const {
			return name;
		}

		int get_value() const {
			return value;
		}

		bool get_key() const {
			return key_item;
		}
	
		int get_count() const {
			return count;
		}

	// Setters --> do any of these need to be pointers?
		void set_name(string new_name) {
			name = new_name;
		}
		
		void set_value(int new_value) {
			value = new_value;
		}

		void set_key(bool new_key) {
			key_item = new_key; 
		}

		void set_count(int new_count) {
			count = new_count;
		}

	// Operators
		bool operator<(const Item& other) const {
			return name < other.name;
		}
		bool operator==(const Item& other) const {
			return name == other.name;
		}

		friend ostream& operator<<(ostream& outs, const Item& item) {
			outs << item.name << ": " << item.count;
			return outs;
		}
			
		friend class Inventory_BST;

};

