#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include "globals.hpp"

struct Point;
struct Paddle;
struct Block;
struct Ball;
Paddle create_new_paddle(Point** buffer, int starting_array_index, int size, int row, char symbol);
Block create_new_block(Point** buffer, char symbol, int row, int col, int length);

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
	Paddle(int size) : _size(size) {};
	~Paddle();
	int _size;
	Point** m_nodes;
	enum Direction m_direction;
	void determine_new_position(Point* (*board)[COL]);
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
