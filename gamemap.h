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

	mvwaddstr(a,0,0, "Game 1: BLACKJACK\n");						//writing to each window
	wbkgd(a, COLOR_PAIR(1));										//assigning color pair to each window
	wrefresh(a);
	
	mvwaddstr(b,0,0, "Game 2: RIDE THE BUS\n");
	wbkgd(b, COLOR_PAIR(2));
	wrefresh(b);

	mvwaddstr(c,0,0, "Game 3: SLOTS\n");
	wbkgd(c, COLOR_PAIR(3));
	wrefresh(c);

	mvwaddstr(d,0,0, "Game 4: RUSSIAN ROULETTE - MUST ACQUIRE $50 TO PLAY\n");
	wbkgd(d, COLOR_PAIR(4));
	wrefresh(d);
	getchar();

	endwin();
	return 0;
}

