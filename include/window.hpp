#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "globals.hpp"
#include "elements.hpp"

struct Window {
	Window();
	Point* m_board[ROW][COL] = {};
	int m_lives;
	// void update_display(Paddle &paddle, Ball &ball, Block (&block_list)[15]);
	void tick(int fps);
	void clear();
	void terminate(Ball &ball, bool &running);

	void clear_display();
	void draw_display(int fps);
	void update_board(Point** buffer, int buffer_size);
};

#endif
