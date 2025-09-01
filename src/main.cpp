#include <thread>
#include "input.hpp"
#include "window.hpp"
#include "elements.hpp"

int main() {
	Input input;
	Window window;
	Paddle paddle;
	Ball ball;

	bool running = true;
	std::thread input_thread(&Input::get_input, &input, std::ref(running), std::ref(paddle));

	while (running) {
		window.update_display(paddle, ball);
		paddle.get_new_pos();
		ball.check_collision();
		ball.get_new_pos();
	}
	input_thread.join();
	return 0;
}
