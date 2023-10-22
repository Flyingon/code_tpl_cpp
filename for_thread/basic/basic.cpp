#include <iostream>
#include <thread>

static bool is_Finished = false;

void DoWork() {
	using namespace std::literals::chrono_literals;

	std::cout << "Started thread id=" << std::this_thread::get_id() << std::endl;
	while (!is_Finished) {
		std::cout << "Working...\n";
		std::this_thread::sleep_for(1s);
	}
}

void DoWork2(const std::string &arg1, std::vector<std::string> *args) {
    (*args).push_back(arg1);
    }



int main() {
	std::thread worker(DoWork);

    std::vector<std::string> args;
    std::thread worker2(DoWork2, "abc", &args);

	std::cin.get();
	is_Finished = true;

	worker.join();
    worker2.join();
	std::cout << "Finished." << std::endl;
	std::cout << "Started thread id=" << std::this_thread::get_id() << std::endl;
}