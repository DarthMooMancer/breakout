#include <thread>
#include <iostream>
#include <engine.hpp>
#include "globals.hpp"
#include <input.hpp>
#include <window.hpp>

int main() {
	const int buffer_size = 50, block_buffer_size = 15;
	bool running = true;
	vec2* buffer[buffer_size] = {};
	Input input;
	Window window;

	Ball ball = create_new_ball(buffer, 0, 1, -1, (ROW - 5), (COL / 2), '*' );
	Paddle paddle = create_new_paddle(buffer, 1, 3, ROW - 2, '-');
	Block** block_buffer = create_block_buffer('3', 3, 5, 3);
	rasterize_buffer(buffer, block_buffer, 4);

	std::thread input_thread([&] { input.get_input(running, paddle.m_direction); } );

	while (running) {
		paddle.determine_new_position(window.m_board);
		paddle.check_collision(ball);
		trim_block_buffer_on_collision(buffer, buffer_size, block_buffer, block_buffer_size, ball);
		ball.determine_new_position(paddle.m_hearts, (ROW - 5), (COL / 2));
		window.clear_display();
		window.update_board(buffer, buffer_size);
		window.draw_display(FPMS);
		if(paddle.m_hearts <= 0) {
			running = false;
			std::cout << "No Hearts left! You lose!\n";
		}
		if(is_block_buffer_empty(block_buffer, block_buffer_size)) {
			running = false;
			std::cout << "No Blocks left! You win!\n";
		}
		std::cout << "Hearts left: " << paddle.m_hearts << "\n";
	}

	input_thread.join();
	cleanup(block_buffer, block_buffer_size);

	return 0;
}
