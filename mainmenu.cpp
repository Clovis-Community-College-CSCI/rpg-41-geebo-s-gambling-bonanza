#include <ncurses.h>
#include <string> 
#include <vector>
using namespace std;

int starting_balance = 55; //placeholder for testing

void init_colors() {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);		//starting screen
	init_pair(2, COLOR_GREEN, COLOR_BLACK);		//main menu
	init_pair(3, COLOR_RED, COLOR_BLACK);		//blackjack starting screen
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);	//ride the bus starting screen
	init_pair(5, COLOR_CYAN, COLOR_BLACK);		//slot machine starting screen
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);	//russian roulette starting screen
	
}
void start_screen() {
	clear();
	bkgd(COLOR_PAIR(1));
	mvprintw(LINES / 2 -2, (COLS - 20) / 2, "WELCOME TO GEEBO'S GAMBLING BONANZA!");
	mvprintw(LINES / 2, (COLS - 25) / 2, "Press any key to continue...");
	refresh();
	getch();
}
void blackjack_screen() {
	clear();
	bkgd(COLOR_PAIR(3));
	mvprintw(LINES / 2 -2, (COLS - 12) / 2, "WELCOME TO BLACKJACK");
	mvprintw(LINES / 2, (COLS - 30) / 2, "Press any key to continue...");
	refresh();
	getch();
}
void ridethebus_screen() {
	clear();
	bkgd(COLOR_PAIR(4));
	mvprintw(LINES / 2 -2, (COLS - 14) / 2, "WELCOME TO RIDE THE BUS");
	mvprintw(LINES / 2, (COLS - 30) / 2, "Press any key to continue...");
	refresh();
	getch();
}
void slots_screen() {
	clear();
	bkgd(COLOR_PAIR(5));
	mvprintw(LINES / 2 -2, (COLS - 13) / 2, "WELCOME TO SLOTS");
	mvprintw(LINES / 2, (COLS - 30) / 2, "Press any key to continue...");
	refresh();
	getch();
}
void roulette_screen() {
	clear();
	bkgd(COLOR_PAIR(6));
	if (starting_balance < 50) {
	mvprintw(LINES / 2 -2, (COLS - 20) / 2, "INSUFFICIENT FUNDS - OBTAIN $50 TO PLAY");
	mvprintw(LINES / 2, (COLS - 25) / 2, "Press any key to continue...");
	}else {
	mvprintw(LINES / 2 -2, (COLS - 15) / 2, "WELCOME TO RUSSIAN ROULETTE");
	mvprintw(LINES / 2, (COLS - 30) / 2, "Press any key to continue...");
	}
	refresh();
	getch();
}

void main_menu() {
	vector<string> options = {"1. BlackJack", "2. Ride the Bus", "3. Slots" ,"4. Russian Roulette", "5. Exit"};
	int choice = 0;
	int ch;

	while (true) {
		clear();
		bkgd(COLOR_PAIR(2));
		mvprintw(2, (COLS - 15) /2, "MAIN MENU");

		for (int i = 0; i < options.size(); i++) {
			if (i == choice) {
				attron(A_REVERSE);
				mvprintw(4+i, (COLS - options[i].size()) / 2, options[i].c_str());
				attroff(A_REVERSE);
			} else {
				mvprintw(4+i, (COLS - options[i].size()) / 2, options[i].c_str());
			}
		}
		ch = getch();

		switch (ch) {
			case KEY_UP:
			choice = (choice == 0) ? options.size() - 1 : choice - 1;
			break;
			case KEY_DOWN:
			choice = (choice == options.size() - 1) ? 0 : choice + 1;
			break;

			case 10: //user enter key
			if (choice == 0) {
				blackjack_screen();
			} else if (choice == 1) {
				ridethebus_screen();
			} else if (choice == 2) {
				slots_screen();
			} else if (choice == 3) {
				roulette_screen();
			} else if (choice == 4) {
				return;
			}
			break;
		}
	}
}

int main() {
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	
	init_colors();
	start_screen();
	main_menu();

	endwin();
	return 0;
}
