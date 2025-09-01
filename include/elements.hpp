#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

struct Point {
	Point();
	int m_row;
	int m_col;
	void assign(int row, int col);
	void to_string();
};

struct Ball {
	Ball();
	Point m_origin;
	int vx;
	int vy;
	void get_new_pos();
	void check_collision(int &lives);
	void change_velocity(char d);
};

struct Paddle {
	Paddle();
	int _size;
	Point m_nodes[3];
	void get_new_pos();
	void check_collision(Ball &ball);
};

struct Block {
	Block(char symbol, int row, int col);
	int _size;
	bool _deleted;
	char m_symbol;
	Point m_nodes[3];
	void get_pos();
	void check_collision(Ball &ball, int &blocks_left);
	void _delete();
};

#endif
