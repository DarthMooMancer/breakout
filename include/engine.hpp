#pragma once

#include "globals.hpp"

struct vec2;
struct Paddle;
struct Block;
struct Ball;
Paddle create_new_paddle(vec2** buffer, int starting_array_index, int size, int row, char symbol);
Ball create_new_ball(vec2** buffer, int buffer_index, int default_vx, int default_vy, int row, int col, char symbol);
Block** create_block_buffer(int starting_symbol, int rows, int cols, int length);
void rasterize_buffer(vec2** buffer, Block** block_buffer, int offset);
void trim_block_buffer_on_collision(vec2** buffer, const int buffer_size, Block** block_buffer, const int block_buffer_size, Ball &ball);
void cleanup(Block** block_buffer, int block_buffer_size);
bool is_block_buffer_empty(Block** block_buffer, int block_buffer_size);

enum Direction { LEFT, RIGHT, NONE };

struct vec2 {
	vec2() : y(0), x(0) {};
	vec2(int row, int col, char symbol) : y(row), x(col), m_symbol(symbol) {};
	int x, y;
	char m_symbol;
	void assign(int row, int col);
};

struct Ball {
	Ball(int default_vx, int default_vy) : vx(default_vx), vy(default_vy) {};
	~Ball();
	vec2* m_origin;
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
	vec2** m_nodes;
	enum Direction m_direction;
	void determine_new_position(vec2* (*board)[COL]);
	void check_collision(Ball &ball);
};

struct Block {
	Block();
	Block(int size, int row, int col, char symbol);
	~Block();
	int _size;
	vec2** m_nodes;
	bool check_collision(Ball &ball);
};

// class Engine {
//
// };
