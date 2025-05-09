#include <iostream>
#include <vector>
#include <random>
#include "playerclass.h"
#include "enemyclass.h"
#include <cstdlib>
#include <ctime>
using namespace std;

//TODO: Replace these games' distribution with distributions from the player and enemy class

//////////////
//BLACK JACK//
//////////////

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

void slots() {
    symbols r1 = symbols(rand() % 3);
    symbols r2 = symbols(rand() % 3);
    symbols r3 = symbols(rand() % 3);

    cout << names[r1] << " | " << names[r2] << " | " << names[r3] << "\n";

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
	random_device rd;  // a seed source for the random number engine
    mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    cout << uniform_int_distribution<> distrib(1, 4);
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


