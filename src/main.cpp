#include <thread>
#include <iostream>
#include "globals.hpp"
#include "input.hpp"
#include "window.hpp"
#include "elements.hpp"

int main() {
	int buffer_size = 50, buffer_block_size = 15;
	bool running = true;
	Point* buffer[50] = {};
	Input input;
	Window window;

	Paddle paddle = create_new_paddle(buffer, 1, 3, ROW - 2, '-');
	Ball ball = create_new_ball(buffer, 0, 1, -1, (ROW - 5), (COL / 2), '*' );
	Block** block_buffer = create_block_buffer(4, '3', 3, 5, 3);
	rasterize_buffer(buffer, block_buffer, 4);

	std::thread input_thread([&] { input.get_input(running, paddle.m_direction); } );

	while (running) {
		paddle.determine_new_position(window.m_board);
		paddle.check_collision(ball);
		trim_block_buffer_on_collision(buffer, buffer_size, block_buffer, buffer_block_size, ball);
		ball.determine_new_position();
		window.clear_display();
		window.update_board(buffer, 50);
		window.draw_display(FPMS);
	}
	input_thread.join();
	for(int i = 0; i < buffer_block_size; i++) {
		delete block_buffer[i];
	}
	delete[] block_buffer;
	for(int i = 0; i < 50; i++) {
		delete buffer[i];
	}
	return 0;
}
