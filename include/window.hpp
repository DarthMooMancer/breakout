#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "globals.hpp"
#include "elements.hpp"

struct Window {
	Point* m_board[ROW][COL] = {};
	void clear_display();
	void draw_display(int fps);
	void update_board(Point** buffer, int buffer_size);
};

#endif
