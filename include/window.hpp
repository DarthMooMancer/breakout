#pragma once
#include <engine.hpp>
#include "globals.hpp"

struct Window {
	vec2* m_board[ROW][COL] = {};
	void clear_display();
	void draw_display(int fps);
	void update_board(vec2** buffer, int buffer_size);
};
