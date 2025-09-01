#include <ncurses.h>
#include "input.hpp"
#include "globals.hpp"

void Input::get_input(bool &running, Paddle &paddle) {
	while(running) {
		initscr();
		cbreak();
		noecho();
		m_getch = getch();
		endwin();

		if(m_getch == 'a' && paddle.m_nodes[0].m_col > 0) {
			paddle.m_nodes[0].m_col--;
			m_getch = ' ';
		} else if(m_getch == 'd' && paddle.m_nodes[paddle._size - 1].m_col < COL - 1) {
			paddle.m_nodes[0].m_col++;
			m_getch = ' ';
		} if(m_getch == 'q') running = false;
	}
}
