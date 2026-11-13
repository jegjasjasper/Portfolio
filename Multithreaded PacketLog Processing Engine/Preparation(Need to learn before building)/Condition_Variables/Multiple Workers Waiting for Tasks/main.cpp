
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

int availableTasks = 0;
bool shutdownWorkers = false;

std::mutex mtx;
std::condition_variable cv;

void worker(/*int id*/) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        // TODO:
        // Wait until tasks are available
        // OR shutdownWorkers becomes true.
        cv.wait(lock, [] {    return (availableTasks > 0) || (shutdownWorkers == true);    });
        // TODO:
        // If shutting down and no tasks remain, exit.
        if ((availableTasks == 0) && (shutdownWorkers == true)){
            return;
        }
        // TODO:
        // Consume one task.
            availableTasks -= 1;

        lock.unlock();

        // Simulate task execution.
        std::this_thread::sleep_for(
            std::chrono::milliseconds(100)
        );
    }
}

void controller() {

    for (int i = 0; i < 10; i++) {
        std::lock_guard<std::mutex> lock(mtx);
        // TODO:
        // Produce one task.
        availableTasks += 1;
        // Notify all workers.
        cv.notify_all();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(200)
        );
    }

    // TODO:
    // Activate shutdown.
    shutdownWorkers = true;
    // Notify all workers again.
    cv.notify_all();
}

int main() {
    std::vector<std::thread> workers;

    for (int i = 0; i < 4; i++) {
        workers.emplace_back(worker/*, i + 1*/);
    }

    std::thread producer(controller);

    // TODO:
    // Join the producer.
    producer.join();
    // Join all workers.
    for (auto& w : workers){
        w.join();
    }

    std::cout << "All tasks completed.\n";

    return 0;
}
