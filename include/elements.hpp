#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

struct Point;
struct Paddle;
struct Block;
struct Ball;
Paddle create_new_paddle(int size);

enum Direction {
	LEFT = -1,
	RIGHT = 1,
	NONE = 0,
};

struct Point {
	Point();
	Point(int row, int col, char symbol) : m_row(row), m_col(col), m_symbol(symbol) {};
	int m_row;
	int m_col;
	char m_symbol;
	void assign(int row, int col);
};

struct Ball {
	Ball();
	Point m_origin;
	int vx;
	int vy;
	int m_blocks_left;
	void get_new_pos();
	void check_collision();
	void change_velocity(char d);
};

struct Paddle {
	Paddle();
	int _size;
	Point m_nodes[3];
	enum Direction m_direction;
	void get_new_pos();
	void check_collision(Ball &ball);
};

struct Block {
	Block(char symbol, int row, int col);
	int _size;
	int _deleted;
	char m_symbol;
	Point m_nodes[3];
	void get_pos();
	void check_collision(Ball &ball, int &blocks_left);
	void _delete();
};

#endif
