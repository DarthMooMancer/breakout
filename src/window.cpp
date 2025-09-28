#include "window.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Window::Window() {
	m_lives = 3;
}
void Window::tick(int fps) {
	std::this_thread::sleep_for(std::chrono::milliseconds(fps)); // 1000 / fps; 200ms = 5fps
}

void Window::clear() {
	std::cout << "\033[H" << std::flush;
}

void Window::terminate(Ball &ball, bool &running) {
	if(m_lives <= 0) {
		clear();
		std::cout << "You lose!" << std::endl;
		running = false;
	} if(ball.m_blocks_left <= 0) {
		clear();
		std::cout << "You win!" << std::endl;
		running = false;
	}
}

void Window::clear_display() {
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COL; j++) {
			m_board[i][j] = nullptr;
		}
	}
}

void Window::update_display(Point** segments, int segments_size) {
	for(int i = segments_size - 1; i >= 0; i--) {
		if(segments[i] != nullptr) {
			m_board[segments[i]->m_row][segments[i]->m_col] = segments[i];
		}
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
