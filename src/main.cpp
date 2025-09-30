#include <thread>
#include <iostream>
#include "globals.hpp"
#include "input.hpp"
#include "window.hpp"
#include "elements.hpp"

int main(int argc, char **argv) {
	Input input;
	Window window;
	// Ball ball;

	Point* buffer[50] = {};
	Paddle paddle = create_new_paddle(buffer, 1, 3, ROW - 2, '-');

	// Block block_list[15] = {
	// 	Block('3', 1, 0), Block('3', 1, 3), Block('3', 1, 6), Block('3', 1, 9), Block('3', 1, 12),
	// 	Block('2', 2, 0), Block('2', 2, 3), Block('2', 2, 6), Block('2', 2, 9), Block('2', 2, 12),
	// 	Block('1', 3, 0), Block('1', 3, 3), Block('1', 3, 6), Block('1', 3, 9), Block('1', 3, 12),
	// };
	Block block = create_new_block('3', 0, 0, 3);
	for(int i = 0; i < block._size; i++) {
		// if(buffer[i + 4] == nullptr) std::cout << "block point is a nullptr\n";
		buffer[i + 4] = block.m_nodes[i];
	}

	bool running = true;
	std::thread input_thread([&] { input.get_input(running, paddle.m_direction); } );

	while (running) {
		// window.update_display(paddle, ball, block_list);
		// 	paddle.m_direction = RIGHT;
		// 	for(int i = 0; i < 8; i++) {
		// 		paddle.m_direction = RIGHT;
		// 	}
		// for(int i = 0; i < 10; i++) {
		// 	if(buffer[i] == nullptr) continue;
		// 	buffer[i]->to_string();
		// }
		// ball.check_collision();
		// for(int i = 0; i < 15; i++) {
		// 	if(block_list[i]._deleted) {
		// 		continue;
		// 	}
		// 	block_list[i].get_pos();
		// 	block_list[i].check_collision(ball, ball.m_blocks_left);
		// }
		// if(ball.m_origin.m_row >= ROW -1) {
		// 	window.m_lives--;
		// 	ball.m_origin.assign(ROW - 7, (COL / 2));
		// 	ball.change_velocity('y');
		// 	// window.update_display(paddle, ball, block_list);
		// 	window.tick(FPMS);
		// }

		// paddle.check_collision(ball);
		// ball.get_new_pos();
		// window.terminate(ball, running);
		paddle.determine_new_position(window.m_board);
		window.clear_display();
		window.update_display(buffer, 50);
		window.draw_display(FPMS);
	}
	input_thread.join();
	for(int i = 0; i < 50; i++) {
		if(buffer[i] == nullptr) continue;
		delete buffer[i];
	}
	return 0;
}
