#include "window.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Window::tick(int fps) {
	std::this_thread::sleep_for(std::chrono::milliseconds(fps)); // 1000 / fps; 200ms = 5fps
}

void Window::update_display(Paddle &paddle, Ball &ball, Block (&block_list)[15]) {
	for(std::array<char, COL> &row : m_board) { row.fill('.'); }
	for(int i = 0; i < paddle._size; i++) {
		m_board[paddle.m_nodes[i].m_row][paddle.m_nodes[i].m_col] = '-';
	}
	for(int i = 0; i < 15; i++) {
		for(int j = 0; j < block_list[i]._size; j++) {
			m_board[block_list[i].m_nodes[j].m_row][block_list[i].m_nodes[j].m_col] = block_list[i].m_symbol;
		}
	}
	m_board[ball.m_origin.m_row][ball.m_origin.m_col] = '*';
	std::cout << "\033[H" << std::flush;
	for(std::array<char, COL> &row : m_board) {
		for(char &col : row) {
			std::cout << col << " ";
		}
		std::cout << "\r\n";
	}
	tick(150);
}
