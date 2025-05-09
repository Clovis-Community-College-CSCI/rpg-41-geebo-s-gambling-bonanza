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

string suitToString(Suit s) {
    switch (s) {
        case DIAMOND: return "Diamond";
        case CLUB:    return "Club";
        case SPADE:   return "Spade";
        case HEART:   return "Heart";
        default:      return "Unknown";
    }
}


class Card {
public:
    Suit suit;
    bool red;
    int value;

    Card(Suit newSuit, int newVal) : suit(newSuit), value(newVal) {
        red = (suit == DIAMOND || suit == HEART);
    }

    static Suit randSuit() {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, 3);
        return static_cast<Suit>(dist(gen));
    }

    static int randVal() {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<int> dist(1, 13);
        return dist(gen);
    }

    static int randBJval() {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<int> dist(1, 10);
        return dist(gen);
    }
};

////////////////
//PLAYER CLASS//
////////////////

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
