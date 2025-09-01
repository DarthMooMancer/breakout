#include <iostream>
#include <thread>
#include "input.hpp"
#include "window.hpp"

int main() {
	Input input;
	Window window;

	bool running = true;
	std::thread input_thread(&Input::get_input, &input, std::ref(running));

	while (running) {
		std::cout << "Hello World" << std::endl;
		window.update_display();
	
	}
	input_thread.join();
	return 0;
}
