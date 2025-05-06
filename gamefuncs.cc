#include <iostream>
#include <vector>
#include <random>
#include "playerclass.h"
#include "enemyclass.h"
using namespace std;

auto blackjack(){

}

auto ridedabus(){

}


enum symbols{
	CHERRY,
	SEVEN,
	BELL,
};

auto slots(){

}

auto russrou(){

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
		ridedabus();
	}
	else if(temp==3){
		slots();
	}
	else if(temp==4){
		russrou();
	}else { return 0; }
	return 0;
}


