#include <ncurses.h>
#include <string> 
#include <vector>
using namespace std;

void init_colors() {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);	//starting screen
	init_pair(2, COLOR_GREEN, COLOR_BLACK);	//main menu
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);	//games screen placeholder
	
}
void start_screen() {
	clear();
	bkgd(COLOR_PAIR(1));
	mvprintw(LINES / 2 -2, (COLS - 20) / 2, "WELCOME TO GEEBO'S GAMBLING CASINO!");
	mvprintw(LINES / 2, (COLS - 25) / 2, "Press any key to continue...");
	refresh();
	getch();
}

void main_menu() {
	vector<string> options = {"1. BlackJack", "2. Ride the Bus", "3. Slots" , "4. Exit"};
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

			case 10: //enter key
			if (choice == options.size() -1) {
				return;
			} else {
				//Placeholder for game screens
					clear();
					bkgd(COLOR_PAIR(3));
					mvprintw(LINES / 2, (COLS - 30) / 2, "You selected: %s", options[choice].c_str());
					mvprintw(LINES / 2 + 2, (COLS - 30) / 2, "Press any key to return...");
					refresh();
					getch();
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
