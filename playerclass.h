#include <iostream>
#include <vector>
#include <random>
using namespace std;

//REMEMBER: uniform_int_distribution

//////////////
//CARD CLASS//
//////////////

enum Suit{
	DIAMOND,
	CLUB, 
	SPADE,
	HEART
};

class Deck{
	public:
	Suit suit;
	bool red;
	int value;

	Deck(Suit &newSuit, int newVal) : suit(newSuit), value(newVal){}
	
	Suit randSuit(){
		random_device rd;  // a seed source for the random number engine
    	mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    	return uniform_int_distribution<> distrib(1, 4);
	}
	
	int randVal(){
		random_device rd;  // a seed source for the random number engine
    	mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    	return uniform_int_distribution<> distrib(1, 13);
	}
	
	int randBJval(){
		random_device rd;  // a seed source for the random number engine
    	mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    	return uniform_int_distribution<> distrib(1, 10);
	}


};	

class Player{
	private:
	
		int cash;

	
	public:

		int getCash()const{
			return cash;
		}
		int setCash(int &newCash){
			cash = newCash;
		}
};
class Cheater:public Player{
	

};
