#include <iostream>
#include "Bridges.h"
#include "CircDLelement.h"
#include <string>

using namespace bridges;
using std::string;

// g++ -g -std=c++23 list.cc -lcurl -lbridges


int main(int argc, char **argv) {
	// create Bridges object
	Bridges bridges (3, "JunKuang",
		"267242104525");

	// node
	CircDLelement<string>  *el0 = new CircDLelement<string> ("Gretel Chaney", "Gretel Chaney");
	CircDLelement<string>  *el1 = new CircDLelement<string> ("Lamont Kyler", "Lamont Kyler");
	CircDLelement<string>  *el2 = new CircDLelement<string> ("Lamont", "Lamont");

	// list
	CircDLelement_List<string> list(el0);
    auto iter = list.begin();

	el0->setNext(el1);
	el1->setPrev(el0);
	el1->setNext(el2);
	el2->setPrev(el0);
	
	bridges.setDataStructure(el0);
	bridges.visualize();

	delete el0;
	delete el1;
	delete el2;

	return 0;
}
