#include "window.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Window::clear_display() {
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			m_board[i][j] = nullptr;
		}
	}
}

void Window::update_board(vec2** buffer, int buffer_size) {
	for(int i = buffer_size - 1; i >= 0; i--) {
		if(buffer[i] == nullptr) continue;
		m_board[buffer[i]->y][buffer[i]->x] = buffer[i];
	}
}

void Window::draw_display(int fps) {
	std::cout << "\033[H" << std::flush;
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			if(m_board[i][j] != nullptr) std::cout << m_board[i][j]->m_symbol << " ";
			else std::cout << ". ";
		}
		std::cout << "\r\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(fps));
}
