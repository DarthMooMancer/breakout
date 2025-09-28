#ifndef INPUT_HPP
#define INPUT_HPP
#include "elements.hpp"

struct Input {
	int m_getch;
	void get_input(bool &running, enum Direction &dir);
};

#endif // INPUT_HPP
