#include <iostream>
#include "elements.hpp"
#include "globals.hpp"

Point::Point() {
	m_row = 0;
	m_col = 0;
}

void Point::to_string() {
	std::cout << "(" << m_row << ", " << m_col <<  ")\n";
}

void Point::assign(int row, int col) {
	m_row = row;
	m_col = col;
}

Paddle create_new_paddle(Point** segments, int index, int size, int row, char symbol) {
	Paddle paddle { size };
	paddle._size = size;
	paddle.m_nodes = new Point*[size];
	for(int i = 0; i < size; i++) {
		paddle.m_nodes[i] = new Point { row, ((COL / 2) - (size / 2)) + i, symbol };
		// paddle.m_nodes[i] = new Point { row, ((COL / 2) - (size / 2) - 1) + i, symbol };
		segments[i + index] = paddle.m_nodes[i];
	}

	return paddle;
}

Paddle::~Paddle() {
	delete[] m_nodes;
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

// void Paddle::check_collision(Ball &ball) {
// 	for(int i = 0; i < _size; i++) {
// 		if(ball.m_origin.m_row == m_nodes[i].m_row) {
// 			if(ball.m_origin.m_col == m_nodes[i].m_col) {
// 				ball.change_velocity('y');
// 			}
// 		}
// 	}
// }

Ball::Ball() {
	m_origin.assign(ROW - 5, (COL / 2));
	vx = 1;
	vy = -1;
	m_blocks_left = 15;
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

void Ball::check_collision() {
	if(m_origin.m_row <= 0) {
		change_velocity('y');
	} if(m_origin.m_col <= 0 || m_origin.m_col >= COL -1) {
		change_velocity('x');
	}
}

void Ball::get_new_pos() {
	if(vx == -1) {
		m_origin.m_col--;
	} else if(vx == 1) {
		m_origin.m_col++;
	} if(vy == -1) {
		m_origin.m_row--;
	} else if(vy == 1) {
		m_origin.m_row++;
	}
}

Block::Block(char symbol, int row, int col) {
	_size = 3;
	_deleted = false;
	m_symbol = symbol;
	m_nodes[0].m_col = col;
	for(int i = 0; i < _size; i++) {
		m_nodes[i].m_row = row;
	}
}

void Block::get_pos() {
	for(int i = 1; i < _size; i++) {
		m_nodes[i].m_col = m_nodes[0].m_col + i;	
	}
}

void Block::_delete() {
	for(int i = 0; i < _size; i++) {
		m_nodes[i].assign(ROW - 1, COL - 1);
		m_symbol = '.';
		_deleted = true;
	}
}

void Block::check_collision(Ball &ball, int &blocks_left) {
	for(int i = 0; i < _size; i++) {
		if(m_nodes[i].m_col == ball.m_origin.m_col) {
			if(m_nodes[i].m_row == ball.m_origin.m_row) {
				ball.change_velocity('y');
				_delete();
				blocks_left--;
			}
		}
	}
}
