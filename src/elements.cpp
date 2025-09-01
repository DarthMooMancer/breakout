#include "elements.hpp"
#include "globals.hpp"
#include <iostream>

Point::Point() {
	m_row = 0;
	m_col = 0;
}

void Point::assign(int row, int col) {
	m_row = row;
	m_col = col;
}

void Point::to_string() {
	std::cout << "(" << m_row << ", " << m_col << ")";
}

Paddle::Paddle() {
	_size = 3;
	m_nodes[0].m_col = 6;
	for(int i = 0; i < _size; i++) {
		m_nodes[i].m_row = ROW - 2;
	}
}

void Paddle::get_new_pos() {
	for(int i = 1; i < _size; i++) {
		m_nodes[i].m_col = m_nodes[0].m_col + i;	
	}
}

void Paddle::check_collision(Ball &ball) {
	for(int i = 0; i < _size; i++) {
		if(ball.m_origin.m_row == m_nodes[i].m_row) {
			if(ball.m_origin.m_col == m_nodes[i].m_col) {
				ball.change_velocity('y');
			}
		}
	}
}

Ball::Ball() {
	m_origin.assign(ROW - 5, (COL / 2));
	vx = 1;
	vy = -1;
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

void Ball::check_collision(int &lives) {
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
