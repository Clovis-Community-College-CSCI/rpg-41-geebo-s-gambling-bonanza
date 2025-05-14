#include <iostream>
#include <vector>
#include <random>
//#include "inventory.h"
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

enum Property{
	CHEAT,
	DOUBLE, 
	LUCK,
	HR
};

class Player {
private:
    Property prop;
    int cash;
    // INVENTORY GOES HERE???
//	Inventory_BST inventory;
	// YES IT DOES!!!

public:
    Player(int startingCash = 10) : cash(startingCash), prop(LUCK) {}

    int getCash() const {
        return cash;
    }
    
    void setCash(int newCash) {
        cash = newCash;
    }

    Property getProp() const {
        return prop;
    }
    
    void setProp(Property newProp) {
        prop = newProp;
    }
    
    void addCash(int amount) {
        cash += amount;
    }
    
    // Virtual methods that can be overridden by inheritors
    virtual bool handleLoss(int betAmount) {
        return false; // Default: always lose money on a loss
    }
    
    virtual int modifyWinnings(int winnings) {
        return winnings; // Default: no modification to winnings
    }
    
    virtual int getBlackjackStartingHand() {
        return Card::randBJval() + Card::randBJval(); // Default starting hand
    }
    
    virtual bool improveGameOdds() {
        return false; // Default: no improved odds
    }
};

class Cheater : public Player {
public:
    Cheater(int startingCash = 10) : Player(startingCash) {
        setProp(CHEAT);
    }
    
    // 50% chance to lose no money on games they lost
    bool handleLoss(int betAmount) override {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<int> dist(1, 100);
        
        int roll = dist(gen);
        if (roll <= 50) {
            cout << "Cheater's luck! You didn't lose any money." << endl;
            return true; // Don't lose money
        }
        return false; // Lose money normally
    }
};

class DorN : public Player {
public:
    DorN(int startingCash = 10) : Player(startingCash) {
        setProp(DOUBLE);
    }
    
    // Double or Nothing: double losses and wins
    bool handleLoss(int betAmount) override {
        cout << "Double or Nothing: You lose double!" << endl;
        // We'll handle the actual cash deduction in the game class
        return false;
    }
    
    int modifyWinnings(int winnings) override {
        if (winnings > 0) {
            cout << "Double or Nothing: You win double!" << endl;
            return winnings * 2;
        }
        else if (winnings < 0) {
            // Double the loss
            return winnings * 2;
        }
        return winnings;
    }
};

class HighRoller : public Player {
public:
    HighRoller() : Player(20) { // Start with 20 cash instead of 10
        setProp(HR);
    }
};

class Lucky : public Player {
public:
    Lucky(int startingCash = 10) : Player(startingCash) {
        setProp(LUCK);
    }
    
    // Lucky players start with 10 in blackjack
    int getBlackjackStartingHand() override {
        return 10;
    }
    
    // Better odds of winning other games
    bool improveGameOdds() override {
        return true;
    }
};


/*
class Player{
	private:

		Property prop;
		int cash;
//		INVENTORY GOES HERE???
	
	public:

		int getCash()const{
			return cash;
		}
		int setCash(int &newCash){
			cash = newCash;
		}

		int getProp()const{
            return prop;
        }
        int setProp(int &newProp){
            prop = newProp;
        }

};
class Cheater:public Player{
	

};
class DorN:public Player{


};
class HighRoller:public Player{


};
class Lucky:public Player{


};
*/
