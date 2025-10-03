#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include "globals.hpp"

struct Point;
struct Paddle;
struct Block;
struct Ball;
Paddle create_new_paddle(Point** buffer, int starting_array_index, int size, int row, char symbol);
Ball create_new_ball(Point** buffer, int buffer_index, int default_vx, int default_vy, int row, int col, char symbol);
Block** create_block_buffer(int starting_array_index, int starting_symbol, int rows, int cols, int length);
void rasterize_buffer(Point** buffer, Block** block_buffer, int offset);
void trim_block_buffer_on_collision(Point** buffer, int buffer_size, Block** block_buffer, int &block_buffer_size, Ball &ball);
void cleanup(Block** block_buffer, int block_buffer_size);
bool is_block_buffer_empty(Block** block_buffer, int block_buffer_size);

enum Direction {
	LEFT = -1,
	RIGHT = 1,
	NONE = 0,
};

struct Point {
	Point() : m_row(0), m_col(0) {};
	Point(int row, int col, char symbol) : m_row(row), m_col(col), m_symbol(symbol) {};
	Point(int row, int col, int symbol) : m_row(row), m_col(col), m_symbol(symbol) {};
	int m_row;
	int m_col;
	char m_symbol;
	void assign(int row, int col);
};

struct Ball {
	Ball(int default_vx, int default_vy) : vx(default_vx), vy(default_vy) {};
	~Ball();
	Point* m_origin;
	int vx;
	int vy;
	void determine_new_position(int &paddle_lives, int reset_ball_x, int reset_ball_y);
	void change_velocity(char d);
};

struct Paddle {
	Paddle(int size) : _size(size), m_hearts(3) {};
	~Paddle();
	int _size;
	int m_hearts;
	Point** m_nodes;
	enum Direction m_direction;
	void determine_new_position(Point* (*board)[COL]);
	void check_collision(Ball &ball);
};

struct Block {
	Block();
	Block(int size, int row, int col, char symbol);
	~Block();
	int _size;
	Point** m_nodes;
	bool check_collision(Ball &ball);
};

#endif
