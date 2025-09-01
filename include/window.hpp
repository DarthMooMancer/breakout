#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <array>
#include "globals.hpp"
#include "elements.hpp"

struct Window {
	std::array<std::array<char, COL>, ROW> m_board = {};
	void update_display(Paddle &paddle, Ball &ball, Block (&block_list)[15]);
	void tick(int fps);
};
#endif
