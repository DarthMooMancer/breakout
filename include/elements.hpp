#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

struct Point {
	Point();
	int m_row;
	int m_col;
	void assign(int row, int col);
	void to_string();
};

struct Paddle {
	Paddle();
	int _size;
	Point m_nodes[3];
	void get_new_pos();
};

struct Ball {
	Ball();
	Point m_origin;
	int vx;
	int vy;
	void get_new_pos();
	void check_collision();
	void change_velocity(char d);
};

// struct Block {
//
// };
//
#endif
