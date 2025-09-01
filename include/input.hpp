#ifndef INPUT_HPP
#define INPUT_HPP
#include "elements.hpp"

struct Input {
	char m_getch = ' ';
	void get_input(bool &running, Paddle &paddle);
};

#endif // INPUT_HPP
