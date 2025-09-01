#include "window.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Window::update_display(Paddle &paddle, Ball &ball) {
	for(std::array<char, COL> &row : m_board) { row.fill('.'); }
	for(int i = 0; i < paddle._size; i++) {
		m_board[paddle.m_nodes[i].m_row][paddle.m_nodes[i].m_col] = '-';
	}
	m_board[ball.m_origin.m_row][ball.m_origin.m_col] = '*';
	std::cout << "\033[H" << std::flush;
	for(std::array<char, COL> &row : m_board) {
		for(char &col : row) {
			std::cout << col << " ";
		}
		std::cout << "\r\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(300)); // 1000 / fps; 200ms = 5fps
}
