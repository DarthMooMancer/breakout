#include <thread>
#include <iostream>
#include "globals.hpp"
#include "input.hpp"
#include "window.hpp"
#include "elements.hpp"

int main(int argc, char **argv) {
	Input input;
	Window window;

	Point* buffer[50] = {};
	Paddle paddle = create_new_paddle(buffer, 1, 3, ROW - 2, '-');
	Ball ball = create_new_ball(buffer, 0, 1, -1, (ROW - 5), (COL / 2), '*' );
	Block** block_buffer = create_block_buffer(4, '3', 3, 5, 3);
	rasterize_buffer(buffer, block_buffer, 4);

	bool running = true;
	std::thread input_thread([&] { input.get_input(running, paddle.m_direction); } );

	while (running) {
		paddle.determine_new_position(window.m_board);
		paddle.check_collision(ball);
		trim_block_buffer_on_collision(block_buffer, 15, ball);
		ball.determine_new_position();
		window.clear_display();
		window.update_board(buffer, 50);
		window.draw_display(FPMS);
	}
	input_thread.join();
	for(int i = 0; i < 50; i++) {
		if(buffer[i] == nullptr) continue;
		delete buffer[i];
	}
	delete[] block_buffer;
	return 0;
}
