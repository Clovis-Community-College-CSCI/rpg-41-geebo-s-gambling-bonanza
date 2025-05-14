#include <iostream>
#include <vector>
#include <random>
#include "playerclass.h"
#include <cstdlib>
#include <ctime>
using namespace std;

//TODO: Replace these games' distribution with distributions from the player and enemy class

class Deck{
	public:
	Suit suit;
	bool red;
	int value;

	Deck(Suit &newSuit, int newVal) : suit(newSuit), value(newVal){}
	
	Suit randSuit(){
		default_random_engine generator;										//
    	uniform_int_distribution<int> distribution(0, 3);
		return distribution(generator);
	}
	
	int randVal(){
//		random_device rd;  // a seed source for the random number engine
//    	mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
//    	return uniform_int_distribution<> distrib(1, 13);

		default_random_engine generator;                                        //
        uniform_int_distribution<int> distribution(0, 12);
        return distribution(generator);

	}
	
	int randBJval(){
		random_device rd;  // a seed source for the random number engine
    	mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    	return uniform_int_distribution<> distrib(1, 10);
	}


};	


//////////////
//BLACK JACK//
//////////////

class BlackJack : public Games {
public:
    BlackJack(int min = 10, int max = 500) : Games(min, max) {}

    void playGame(Player &p) override {
        cout << "Welcome to BlackJack!" << endl;
        cout << "Your current cash: $" << p.getCash() << endl;

        if (p.getCash() < minBet) {
            cout << "You don't have enough cash to play BlackJack!" << endl;
            return;
        }

        cout << "Enter your bet ($" << minBet << " - $" << maxBet << "): ";
        int bet;
        cin >> bet;
        setBet(bet);

        if (p.getCash() < currentBet) {
            cout << "You don't have enough cash for that bet!" << endl;
            return;
        }

        // Deduct bet from player's cash
        int playerCash = p.getCash() - currentBet;
        p.setCash(playerCash);

        cout << "You bet $" << currentBet << endl;

        // Use player's custom starting hand (Lucky players get 10)
        int player = p.getBlackjackStartingHand();
        int dealer = Card::randBJval() + Card::randBJval();

        cout << "You start with: " << player << endl;
        cout << "Dealer shows: " << dealer/2 << endl;

        char choice;
        while (player < 21) {
            cout << "Hit (h) or stand (s)? ";
            cin >> choice;
            if (choice == 'h') {
                int card = Card::randBJval();
                player += card;
                cout << "You drew: " << card << ", total: " << player << endl;
            } else break;
        }

        if (player > 21) {
            cout << "Bust! Dealer wins.\n";
            winnings = -currentBet; // player lost their bet

            // Check if player can avoid the loss (Cheater class)
            if (p.handleLoss(currentBet)) {
                winnings = 0; // Reset winnings
                p.addCash(currentBet); // Return the bet
            } else if (p.getProp() == DOUBLE) {
                winnings = p.modifyWinnings(winnings); // Double the loss for DorN
            }
            return;
        }

        cout << "Dealer's turn...\n";
        cout << "Dealer reveals full hand: " << dealer << endl;

        // If player has improved odds (Lucky class), dealer has higher chance to bust
        bool improvedOdds = p.improveGameOdds();

        while (dealer < 17) {
            int card = Card::randBJval();
            // Lucky players make dealer more likely to bust
            if (improvedOdds && dealer > 15) {
                card = min(card + 2, 10); // Increase dealer's chance of busting
            }
            dealer += card;
            cout << "Dealer drew: " << card << ", total: " << dealer << endl;
        }

        cout << "Dealer total: " << dealer << endl;

        if (dealer > 21 || player > dealer) {
            cout << "You win!\n";
            winnings = currentBet; // Player won their bet

            // Check for double winnings (DorN class)
            winnings = p.modifyWinnings(winnings);
        }
        else if (player < dealer) {
            cout << "Dealer wins.\n";
            winnings = -currentBet; // Player lost their bet

            // Check if player can avoid the loss (Cheater class)
            if (p.handleLoss(currentBet)) {
                winnings = 0; // Reset winnings
                p.addCash(currentBet); // Return the bet
            } else if (p.getProp() == DOUBLE) {
                winnings = p.modifyWinnings(winnings); // Double the loss for DorN
            }
        }
        else {
            cout << "It's a tie.\n";
            winnings = 0; // Return the bet to the player
            p.addCash(currentBet);
        }
    }

    void stopGame(Player &p) override {
        if (winnings > 0) {
            cout << "You won $" << winnings << "!" << endl;
            p.addCash(winnings + currentBet); // Return bet + winnings
        } else if (winnings < 0) {
            cout << "You lost $" << -winnings << "." << endl;
            // Already deducted when placing bet
        } else {
            cout << "You broke even." << endl;
        }
        cout << "Your new balance: $" << p.getCash() << endl;
        winnings = 0;
    }
};

//////////////////////////////////
//RIDE THE BUS (FROM SCHEDULE 1)//
//////////////////////////////////

class RideTheBus : public Games {
public:
    RideTheBus(int min = 5, int max = 100) : Games(min, max) {}

    void playGame(Player &p) override {
        cout << "Welcome to Ride the Bus!" << endl;
        cout << "Your current cash: $" << p.getCash() << endl;

        if (p.getCash() < minBet) {
            cout << "You don't have enough cash to play Ride the Bus!" << endl;
            return;
        }

        cout << "Enter your bet ($" << minBet << " - $" << maxBet << "): ";
        int bet;
        cin >> bet;
        setBet(bet);

        if (p.getCash() < currentBet) {
            cout << "You don't have enough cash for that bet!" << endl;
            return;
        }

        // Deduct bet from player's cash
        int playerCash = p.getCash() - currentBet;
        p.setCash(playerCash);

        cout << "You bet $" << currentBet << endl;

        int current = Card::randVal();
        cout << "Starting card: " << current << endl;
        int score = 0;

        bool improvedOdds = p.improveGameOdds();

        while (true) {
            cout << "Will the next card be higher (h) or lower (l)? ";
            char guess;
            cin >> guess;

            int next = Card::randVal();

            // Lucky players get slightly better cards that match their guess
            if (improvedOdds) {
                if (guess == 'h' && next <= current) {
                    static random_device rd;
                    static mt19937 gen(rd());
                    uniform_int_distribution<int> dist(current + 1, 13);
                    if (current < 13) {
                        next = dist(gen); // Get a higher card
                    }
                } else if (guess == 'l' && next >= current) {
                    static random_device rd;
                    static mt19937 gen(rd());
                    uniform_int_distribution<int> dist(1, current - 1);
                    if (current > 1) {
                        next = dist(gen); // Get a lower card
                    }
                }
            }

            cout << "Next card: " << next << endl;

            if ((guess == 'h' && next > current) || (guess == 'l' && next < current)) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "Wrong! Game over. Your score: " << score << endl;
                break;
            }
            current = next;
        }

        // Calculate winnings based on score
        winnings = score * (currentBet / 2);
        if (score == 0) {
            winnings = -currentBet; // Lost their bet

            // Check if player can avoid the loss (Cheater class)
            if (p.handleLoss(currentBet)) {
                winnings = 0; // Reset winnings
                p.addCash(currentBet); // Return the bet
            } else if (p.getProp() == DOUBLE) {
                winnings = p.modifyWinnings(winnings); // Double the loss for DorN
            }
        } else if (winnings > 0) {
            // Check for double winnings (DorN class)
            winnings = p.modifyWinnings(winnings);
        }
    }

    void stopGame(Player &p) override {
        if (winnings > 0) {
            cout << "You won $" << winnings << "!" << endl;
            p.addCash(winnings + currentBet); // Return bet + winnings
        } else if (winnings < 0) {
            cout << "You lost $" << -winnings << "." << endl;
            // Already deducted when placing bet
        } else {
            cout << "You broke even." << endl;
            p.addCash(currentBet); // Return bet only
        }
        cout << "Your new balance: $" << p.getCash() << endl;
        winnings = 0;
    }
};

/////////////////////////
//SLOTS AND SYMBOL ENUM//
/////////////////////////

enum Symbol {
    CHERRY,
    SEVEN,
    BELL
};

const char* symbolNames[] = { "CHERRY", "SEVEN", "BELL" };

class Slots : public Games {
private:
    static string getRandomSymbol(int &num, bool improvedOdds = false) {
        srand(time(0) + num);
        int temp = rand() % 30;
        num++;

        // Lucky players have better odds at getting winning combinations
        if (improvedOdds) {
            temp = max(temp - 5, 0); // Shift distribution to favor better symbols
        }

        if (temp <= 9) {
            return "CHERRY";
        } else if (temp <= 19) {
            return "SEVEN";
        } else {
            return "BELL";
        }
    }

public:
    Slots(int min = 1, int max = 50) : Games(min, max) {}

    void playGame(Player &p) override {
        cout << "Welcome to Slots!" << endl;
        cout << "Your current cash: $" << p.getCash() << endl;

        if (p.getCash() < minBet) {
            cout << "You don't have enough cash to play Slots!" << endl;
            return;
        }

        cout << "Enter your bet ($" << minBet << " - $" << maxBet << "): ";
        int bet;
        cin >> bet;
        setBet(bet);

        if (p.getCash() < currentBet) {
            cout << "You don't have enough cash for that bet!" << endl;
            return;
        }

        // Deduct bet from player's cash
        int playerCash = p.getCash() - currentBet;
        p.setCash(playerCash);

        cout << "You bet $" << currentBet << endl;

        bool improvedOdds = p.improveGameOdds();

        int num = 0;
        string r1 = getRandomSymbol(num, improvedOdds);
        string r2 = getRandomSymbol(num, improvedOdds);
        string r3 = getRandomSymbol(num, improvedOdds);

        // Lucky players have a small chance to get a guaranteed match
        if (improvedOdds) {
            // 20% chance to make the third symbol match the second
            static random_device rd;
            static mt19937 gen(rd());
            uniform_int_distribution<int> dist(1, 100);
            if (dist(gen) <= 20) {
                r3 = r2;
            }
        }

        cout << r1 << " | " << r2 << " | " << r3 << "\n";

        if (r1 == r2 && r2 == r3) {
            cout << "Three of a kind!\n";
            winnings = currentBet * 3; // Triple the bet

            // Check for double winnings (DorN class)
            winnings = p.modifyWinnings(winnings);
        } else if (r1 == r2 || r1 == r3 || r2 == r3) {
            cout << "Two of a kind!\n";
            winnings = currentBet; // Double the bet

            // Check for double winnings (DorN class)
            winnings = p.modifyWinnings(winnings);
        } else {
            cout << "No win.\n";
            winnings = -currentBet; // Lost their bet

            // Check if player can avoid the loss (Cheater class)
            if (p.handleLoss(currentBet)) {
                winnings = 0; // Reset winnings
                p.addCash(currentBet); // Return the bet
            } else if (p.getProp() == DOUBLE) {
                winnings = p.modifyWinnings(winnings); // Double the loss for DorN
            }
        }
    }

    void stopGame(Player &p) override {
        if (winnings > 0) {
            cout << "You won $" << winnings << "!" << endl;
            p.addCash(winnings + currentBet); // Return bet + winnings
        } else if (winnings < 0) {
            cout << "You lost $" << -winnings << "." << endl;
            // Already deducted when placing bet
        } else {
            cout << "You broke even." << endl;
            p.addCash(currentBet); // Return bet only
        }
        cout << "Your new balance: $" << p.getCash() << endl;
        winnings = 0;
    }
};

////////////////////
//RUSSIAN ROULETTE//
////////////////////

class RussianRoulette : public Games {
public:
    RussianRoulette(int min = 50, int max = 1000) : Games(min, max) {}

    void playGame(Player &p) override {
        cout << "Welcome to Russian Roulette!" << endl;
        cout << "Your current cash: $" << p.getCash() << endl;

        if (p.getCash() < minBet) {
            cout << "You don't have enough cash to play Russian Roulette!" << endl;
            return;
        }

        cout << "Enter your bet ($" << minBet << " - $" << maxBet << "): ";
        int bet;
        cin >> bet;
        setBet(bet);

        if (p.getCash() < currentBet) {
            cout << "You don't have enough cash for that bet!" << endl;
            return;
        }

        // Deduct bet from player's cash
        int playerCash = p.getCash() - currentBet;
        p.setCash(playerCash);

        cout << "You bet $" << currentBet << endl;

        char play;
        bool alive = true;
        int rounds = 0;
        bool improvedOdds = p.improveGameOdds();

        do {
            srand(time(0) + rounds);
            int chamber = rand() % 6;
            rounds++;

            // Lucky players have slightly better odds of survival
            if (improvedOdds && chamber == 0) {
                static random_device rd;
                static mt19937 gen(rd());
                uniform_int_distribution<int> dist(1, 100);
                if (dist(gen) <= 30) { // 30% chance to survive when would have died
                    chamber = 1; // Not the lethal chamber
                }
            }

            cout << "You spin the cylinder... pull the trigger...\n";
            if (chamber == 0) {
                cout << "BANG! Welcome to the Afterlife.\n";
                alive = false;
                break;
            } else {
                cout << "Click! You're safe.\n";
                rounds++;
            }

            cout << "Play again? (y/n): ";
            cin >> play;
        } while (play == 'y');

        if (alive) {
            winnings = currentBet * rounds; // Multiply bet by number of rounds survived

            // Check for double winnings (DorN class)
            winnings = p.modifyWinnings(winnings);
        } else {
            winnings = -currentBet; // Lost their bet

            // Check if player can avoid the loss (Cheater class)
            if (p.handleLoss(currentBet)) {
                winnings = 0; // Reset winnings
                p.addCash(currentBet); // Return the bet
            } else if (p.getProp() == DOUBLE) {
                winnings = p.modifyWinnings(winnings); // Double the loss for DorN
            }
        }
    }

    void stopGame(Player &p) override {
        if (winnings > 0) {
            cout << "You won $" << winnings << "!" << endl;
            p.addCash(winnings + currentBet); // Return bet + winnings
        } else if (winnings < 0) {
            cout << "You lost $" << -winnings << "." << endl;
            // Already deducted when placing bet
        } else {
            cout << "You broke even." << endl;
            p.addCash(currentBet); // Return bet only
        }
        cout << "Your new balance: $" << p.getCash() << endl;
        winnings = 0;
    }
};
        } else {
            cout << "You broke even." << endl;
            p.addCash(currentBet); // Return bet only
        }
        cout << "Your new balance: $" << p.getCash() << endl;
        winnings = 0;
    }
};


/*
///////////////////
//GAMES BASECLASS//
///////////////////

class Games {
protected:
    int minBet;
    int maxBet;
    int currentBet;
    int winnings;
public:
    Games(int min = 0, int max = 100) : minBet(min), maxBet(max), currentBet(0), winnings(0) {}
    virtual void playGame(Player &p) = 0;
    virtual void stopGame(Player &p) = 0;
    void setBet(int bet) {
        if (bet < minBet)
            currentBet = minBet;
        else if (bet > maxBet)
            currentBet = maxBet;
        else
            currentBet = bet;
    }
};


//////////////
//BLACK JACK//
/////////////

void blackjack() {
    int player = Card::randBJval() + Card::randBJval();
    int dealer = Card::randBJval() + Card::randBJval();

    cout << "You start with: " << player << endl;
    char choice;
    while (player < 21) {
        cout << "Hit (h) or stand (s)? ";
        cin >> choice;
        if (choice == 'h') {
            int card = Card::randBJval();
            player += card;
            cout << "You drew: " << card << ", total: " << player << endl;
        } else break;
    }

    if (player > 21) {
        cout << "Bust! Dealer wins.\n";
        return;
    }

    cout << "Dealer's turn...\n";
    while (dealer < 17) {
        int card = Card::randBJval();
        dealer += card;
    }
    cout << "Dealer total: " << dealer << endl;

    if (dealer > 21 || player > dealer)
        cout << "You win!\n";
    else if (player < dealer)
        cout << "Dealer wins.\n";
    else
        cout << "It's a tie.\n";
}

//////////////////////////////////
//RIDE THE BUS (FROM SCHEDULE 1)//
//////////////////////////////////

void rideTheBus() {
    int current = Card::randVal();
    cout << "Starting card: " << current << endl;
    int score = 0;

    while (true) {
        cout << "Will the next card be higher (h) or lower (l)? ";
        char guess;
        cin >> guess;

        int next = Card::randVal();
        cout << "Next card: " << next << endl;

        if ((guess == 'h' && next > current) || (guess == 'l' && next < current)) {
            cout << "Correct!\n";
            score++;
        } else {
            cout << "Wrong! Game over. Your score: " << score << endl;
            break;
        }
        current = next;
    }
}

/////////////////////////
//SLOTS AND SYMBOL ENUM//
/////////////////////////


enum symbols{
	CHERRY,
	SEVEN,
	BELL,
};

const char* names[] = { "CHERRY", "SEVEN", "BELL" };


void assign(string &x, int &num){
//	default_random_engine rd;
//    mt19937 generator(rd());
//    uniform_int_distribution<int> distribution(0, 29);

	srand(time(0));
	int temp = (rand() * num) % 30;
//	cerr << num << endl;
	num++;
	if(temp <= 9){
		x = "CHERRY";
	}
	else if(temp <= 19){
		x = "SEVEN";
	}else{
		x = "BELL";
	}
}

void slots() {
	
//    default_random_engine rd;
//	mt19937 generator(rd());
//    uniform_int_distribution<int> distribution(0, 29);
	
	int num = 0;
    string r1;
	assign(r1, num);
    string r2; 
	assign(r2, num);
    string r3;
	assign(r3, num);

    cout << r1 << " | " << r2 << " | " << r3 << "\n";

    if (r1 == r2 && r2 == r3)
        cout << "Three of a kind!\n";				//Add to player cash
    else if (r1 == r2 || r1 == r3 || r2 == r3)
        cout << "Two of a kind!\n";					//Add to player cash
    else
        cout << "No win.\n";						//Subtract from player cash
}

////////////////////
//RUSSIAN ROULLETE//
////////////////////

int russrou() {
    srand(time(0));
    char play;
    do {
        int chamber = rand() % 6;
        cout << "You spin the cylinder... pull the trigger...\n";
        if (chamber == 0)
            cout << "BANG! Welcome to the Afterlife.\n";
        else
            cout << "Click! You're safe.\n";

        cout << "Play again? (y/n): ";
        cin >> play;
    } while (play == 'y');
}

//////////
//DRIVER//
//////////

int main(){
	cout << "1) BLJK\n 2) RDB\n 3) SLOTS\n 4) RR" << endl;
//	random_device rd;  // a seed source for the random number engine
//    mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
//    cout << uniform_int_distribution<> distrib(1, 4);
	int temp;
	cin >> temp;
	if(temp == 1){
		blackjack();
	}
	else if(temp==2){
		rideTheBus();
	}
	else if(temp==3){
		slots();
	}
	else if(temp==4){
		russrou();
	}else { return 0; }
	return 0;
}

*/
