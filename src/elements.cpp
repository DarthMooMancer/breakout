#include "elements.hpp"
#include "globals.hpp"

Paddle create_new_paddle(Point** buffer, int starting_array_index, int size, int row, char symbol) {
	Paddle paddle { size };
	paddle.m_nodes = new Point*[size];
	for(int i = 0; i < size; i++) {
		paddle.m_nodes[i] = new Point { row, ((COL / 2) - (size / 2)) + i, symbol };
		buffer[i + starting_array_index] = paddle.m_nodes[i];
	}

	return paddle;
}

Ball create_new_ball(Point** buffer, int buffer_index, int default_vx, int default_vy, int row, int col, char symbol) {
	Ball ball { default_vx, default_vy };
	ball.m_origin = new Point { row, col, symbol };
	buffer[buffer_index] = ball.m_origin;
	return ball;
}

Block** create_block_buffer(int starting_array_index, int starting_symbol, int rows, int cols, int length) {
	Block** block_buffer = new Block*[rows * cols];
	int row, int_symbol, col;
	char char_symbol;
	for(int index = 0; index < rows * cols; index++) {
		row = index / 5;
		int_symbol = (starting_symbol - '0') - row;
		char_symbol = '0' + int_symbol;
		col = (index % 5) * 3;
		block_buffer[index] = new Block(length, row, col, char_symbol);
	}
	return block_buffer;
}

bool is_block_buffer_empty(Block** block_buffer, int block_buffer_size) {
	int total_clear_blocks = 0;
	for(int block_index = 0; block_index < block_buffer_size; block_index++) {
		if(block_buffer[block_index] != nullptr) continue;
		total_clear_blocks++;
	}

	if(total_clear_blocks == block_buffer_size) return true;
	return false;
}

void cleanup(Block** block_buffer, int block_buffer_size) {
	for(int i = 0; i < block_buffer_size; i++) {
		delete block_buffer[i];
	}
	delete[] block_buffer;
}

void rasterize_buffer(Point** buffer, Block** block_buffer, int offset) {
	for(int block_index = 0; block_index < 15; block_index++) {
		if(block_buffer[block_index] == nullptr) continue;
		for(int node_index = 0; node_index < block_buffer[block_index]->_size; node_index++) {
			buffer[offset + node_index] = block_buffer[block_index]->m_nodes[node_index];
		}
		offset += 3;
	}
}

void trim_block_buffer_on_collision(Point** buffer, int buffer_size, Block** block_buffer, int &block_buffer_size, Ball &ball) {
	for(int i = 0; i < block_buffer_size; i++) {
		if(block_buffer[i] == nullptr) continue;
		if(block_buffer[i]->check_collision(ball)) {
			ball.change_velocity('y');
			for(int a = 0; a < block_buffer[i]->_size; a++) {
				Point* doomed = block_buffer[i]->m_nodes[a];
				for(int j = 0; j < buffer_size; j++) {
					if(buffer[j] == doomed) {
						buffer[j] = nullptr;
					}
				}
			}
			delete block_buffer[i];
			block_buffer[i] = nullptr;
		}
	}
}

Paddle::~Paddle() {
	if(m_nodes) {
		for(int i = 0; i < _size; i++) {
			delete m_nodes[i];
			m_nodes[i] = nullptr;
		}
		delete[] m_nodes;
		m_nodes = nullptr;
	}
}

void Paddle::determine_new_position(Point* (*board)[COL]) {
	if(m_direction == LEFT && m_nodes[0]->m_col - 1 >= 0) {
		m_nodes[0]->m_col--;
		for(int i = 1; i < _size; i++) {
			m_nodes[i]->m_col = m_nodes[0]->m_col + i;
		}
	}
	else if(m_direction == RIGHT && m_nodes[_size - 1]->m_col + 1 < ROW) {
		m_nodes[_size - 1]->m_col++;
		for(int i = 1; i < _size; i++) {
			m_nodes[_size - (i + 1)]->m_col = m_nodes[_size - 1]->m_col - i;
		}
	}
	m_direction = NONE;
}

void Paddle::check_collision(Ball &ball) {
	for(int i = 0; i < _size; i++) {
		if(ball.m_origin->m_row != m_nodes[i]->m_row) continue;
		if(ball.m_origin->m_col != m_nodes[i]->m_col) continue;
		ball.change_velocity('y');
	}
}

Ball::~Ball() {
	delete m_origin;
	m_origin = nullptr;
}

void Ball::change_velocity(char d) {
	if(d == 'x') {
		if(vx == -1) vx = 1;
		else if (vx == 1) vx = -1;
	} else if(d == 'y') {
		if(vy == -1) vy = 1;
		else if (vy == 1) vy = -1;
	}
}

void Ball::determine_new_position(int &paddle_lives, int reset_ball_x, int reset_ball_y) {
	if(m_origin->m_row <= 0) {
		vy = 1;
	} else if(m_origin->m_row >= ROW - 1) {
		paddle_lives--;
		m_origin->m_row = reset_ball_y;
		m_origin->m_col = reset_ball_x;
	}
	if(m_origin->m_col <= 0) {
		vx = 1;
	} else if(m_origin->m_col >= COL - 1) {
		vx = -1;
	}

	m_origin->m_col += vx;
	m_origin->m_row += vy;
}

Block::~Block() {
	if(m_nodes) {
		for(int i = 0; i < _size; i++) {
			delete m_nodes[i];
			m_nodes[i] = nullptr;
		}
		delete[] m_nodes;
		m_nodes = nullptr;
	}
}

Block::Block(int size, int row, int col, char symbol) {
	_size = size;
	m_nodes = new Point*[size];
	for(int i = 0; i < size; i++) {
		m_nodes[i] = new Point { row, col + i, symbol };
	}
}

bool Block::check_collision(Ball &ball) {
	for(int i = 0; i < _size; i++) {
		if(m_nodes[i]->m_col != ball.m_origin->m_col) continue;
		if(m_nodes[i]->m_row != ball.m_origin->m_row) continue;
		return true;
	}
	return false;
}
