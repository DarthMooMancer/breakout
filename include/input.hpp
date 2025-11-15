#pragma once
#include <engine.hpp>

struct Input {
	int m_getch;
	void get_input(bool &running, enum Direction &dir);
};
