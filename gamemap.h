#include <ncurses.h>
#include <stdlib.h>

void bomb() {
	addstr("Unable to allocate memory for new window.\n");
	refresh();
	endwin();
	exit(1);
}

int main (void) {
	WINDOW *a, *b, *c, *d;
	int maxx, maxy, halfx, halfy;

	initscr();
	refresh();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);							//all the color pairs
	init_pair(2, COLOR_BLACK, COLOR_BLUE);							//black font, diff color background/window
	init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(4, COLOR_BLACK, COLOR_CYAN);

	getmaxyx(stdscr, maxy, maxx);									//calculate window sizes && locations
	halfx = maxx / 2;
	halfy = maxy / 2;

	if( (a = newwin(halfy, halfx, 0, 0)) == NULL) bomb();			//creates the 4 windows
	if( (b = newwin(halfy, halfx, 0, halfx)) == NULL) bomb();
	if( (c = newwin(halfy, halfx, halfy, 0)) == NULL) bomb();
	if( (d = newwin(halfy, halfx, halfy, halfx)) == NULL) bomb();

	wbkgd(a, COLOR_PAIR(1));										//assigning color pair to each window
	mvwaddstr(a,0,0, "Game 1: BLACKJACK\n");						//writing to each window
	mvwaddstr(a,2,2, "_____ _____");					
	mvwaddstr(a,3,2, "|A  . | |K   |");					
	mvwaddstr(a,4,2, "|  / . \\  |  |     |");					
	mvwaddstr(a,5,2, "| (_._) |  |      |");					
	mvwaddstr(a,6,2, "|   |   |  |  ♠️  |");					
	mvwaddstr(a,7,2, "|____V| |_____|");					
	wrefresh(a);
	
	wbkgd(b, COLOR_PAIR(2));
	mvwaddstr(b,0,0, "Game 2: RIDE THE BUS\n");
	mvwaddstr(a,2,2, "  ______");					
	mvwaddstr(a,3,2, " /      \\");					
	mvwaddstr(a,4,2, "|  BUS   |");					
	mvwaddstr(a,5,2, "|______|");										
	mvwaddstr(a,7,2, "Get ready to play!");										
	wrefresh(b);

	wbkgd(c, COLOR_PAIR(3));
	mvwaddstr(c,0,0, "Game 3: SLOTS\n");
	mvwaddstr(a,2,2, " _______ ");					
	mvwaddstr(a,3,2, "| 7  |  🍒  |");					
	mvwaddstr(a,4,2, "| BAR |  7 |");					
	mvwaddstr(a,5,2, "| 🍒 |  BAR |");					
	mvwaddstr(a,6,2, " --------");					
	mvwaddstr(a,8,2, "Get ready to spin!");					
	wrefresh(c);

	wbkgd(d, COLOR_PAIR(4));
	mvwaddstr(d,0,0, "Game 4: RUSSIAN ROULETTE - MUST ACQUIRE $50 TO PLAY\n");
	mvwaddstr(a,2,2, "   _____________ ");					
	mvwaddstr(a,3,2, "   |  REVOLVER  |");					
	mvwaddstr(a,4,2, "   |____________| ");					
	mvwaddstr(a,5,2, "        | | ");					
	mvwaddstr(a,6,2, "        (oo)");					
	mvwaddstr(a,7,2, "     --/----\\--");					
	mvwaddstr(a,9,2, "WARNING: $50 TO PLAY!");					
	wrefresh(d);
	getchar();

	endwin();
	return 0;
}

