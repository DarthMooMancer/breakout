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
		m_nodes[i].m_row = 8;

	}
}

void Paddle::get_new_pos() {
	for(int i = 1; i < _size; i++) {
		m_nodes[i].m_col = m_nodes[0].m_col + i;	
	}
}

Ball::Ball() {
	m_origin.assign(ROW - 3, (COL / 2));
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

void Ball::check_collision() {
	if(m_origin.m_row <= 0 || m_origin.m_row >= ROW -1) {
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
