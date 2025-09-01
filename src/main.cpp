#include <iostream>
#include <thread>
#include "input.hpp"
#include "window.hpp"
#include "elements.hpp"

int main() {
	Input input;
	Window window;
	Paddle paddle;
	Ball ball;
	Block block_list[15] = {
		Block('3', 0, 0), Block('3', 0, 3), Block('3', 0, 6), Block('3', 0, 9), Block('3', 0, 12),
		Block('2', 1, 0), Block('2', 1, 3), Block('2', 1, 6), Block('2', 1, 9), Block('2', 1, 12),
		Block('1', 2, 0), Block('1', 2, 3), Block('1', 2, 6), Block('1', 2, 9), Block('1', 2, 12),
	};

	bool running = true;
	int lives = 3;
	std::thread input_thread(&Input::get_input, &input, std::ref(running), std::ref(paddle));

	while (running) {
		window.update_display(paddle, ball, block_list);
		paddle.get_new_pos();
		ball.check_collision(lives);
		for(int i = 0; i < 15; i++) {
			block_list[i].get_pos();
		}
		// if(ball.m_origin.m_row >= ROW -1) {
		// 	lives--;
		// 	ball.m_origin.assign(ROW - 5, (COL / 2));
		// 	ball.vy = 1;
		// 	window.update_display(paddle, ball, block_list);
		// 	window.tick(500);
		// }

		paddle.check_collision(ball);
		ball.get_new_pos();
		// std::cout << "Lives left: " << lives << std::endl;
		// if(lives <= 0) {
		// 	std::cout << "You lose!" << std::endl;
		// 	running = false;
		// } 
	}
	input_thread.join();
	return 0;
}
