
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

int balance = 0;

std::mutex mtx;
std::condition_variable cv;

void withdrawMoney(/*int id,*/ int amount) {
    // TODO:
    // Acquire unique_lock.
    std::unique_lock<std::mutex> ul(mtx);
    // Wait until balance >= amount.
    cv.wait(ul, [amount] {    return balance >= amount;   });
    // Deduct the amount.
    balance -= amount;
    // Print the transaction.
    std::cout << "Balance: %d" << balance << '\n';
}

void depositMoney() {
    for (int i = 0; i < 3; i++) {
        // TODO:
        // Lock the mutex.
        std::lock_guard<std::mutex> lock(mtx);
        // Deposit 500.
        balance += 500;
        // Print the balance.
        std::cout << "Balance: %d" << balance << '\n';
        // Release the mutex.
        // Notify one waiting thread.
        cv.notify_one();

        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }
}

int main() {
    std::thread t1(withdrawMoney/*, 1*/, 300);
    std::thread t2(withdrawMoney/*, 2*/, 500);
    std::thread t3(withdrawMoney/*, 3*/, 700);

    std::thread depositor(depositMoney);

    t1.join();
    t2.join();
    t3.join();
    depositor.join();

    std::cout << "Final balance: " << balance << '\n';

    return 0;
}
