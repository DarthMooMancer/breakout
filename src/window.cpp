#include "window.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Window::update_display() {
	for(std::array<char, COL> &row : m_board) { row.fill('.'); }
	// Modify board
	
	// Refresh and draw screen
	std::cout << "\033[H" << std::flush;
	for(std::array<char, COL> &row : m_board) {
		for(char &col : row) {
			std::cout << col << " ";
		}
		std::cout << "\r\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(130)); // 1000 / fps; 200ms = 5fps
}
