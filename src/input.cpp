#include "input.hpp"
#include <ncurses.h>

void Input::get_input(bool &running) {
	while(running) {
		initscr();
		cbreak();
		noecho();

		m_getch = getch();

		endwin();
		if(m_getch == 'q') {
			running = false;
		}
	}
}
