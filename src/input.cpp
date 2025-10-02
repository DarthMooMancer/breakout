#include <ncurses.h>
#include "input.hpp"

void Input::get_input(bool &running, enum Direction &dir) {
	while(running) {
		initscr();
		cbreak();
		noecho();
		m_getch = getch();
		endwin();

		switch (m_getch) {
			case 67:
				dir = RIGHT;
				break;
			case 68:
				dir = LEFT;
				break;
			case 113:
				running = false;
				break;
		}
	}
}
