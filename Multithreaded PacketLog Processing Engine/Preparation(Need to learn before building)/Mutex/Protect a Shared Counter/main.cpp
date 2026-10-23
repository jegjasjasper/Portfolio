
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void incrementCounter() {
    for (int i = 0; i < 100000; i++) {
        mtx.lock();

        counter++;

        mtx.unlock();
    }
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << '\n';

    return 0;
}
