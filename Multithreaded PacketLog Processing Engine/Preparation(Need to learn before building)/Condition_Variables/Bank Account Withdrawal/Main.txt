
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int balance = 0;

std::mutex mtx;
std::condition_variable cv;

void withdrawMoney(int amount) {
    // TODO:
    // 1. Acquire the mutex using unique_lock.
    std::unique_lock<std::mutex> ul(mtx);
    // 2. Wait until balance >= amount.
    cv.wait(ul, [amount] { return balance >= amount;  });
    // 3. Withdraw the requested amount.
        balance -= amount;
    // 4. Print the remaining balance.
        std::cout << "\nbalance: " << balance;
}

void addMoney(int amount) {
    // TODO:
    // 1. Acquire the mutex.
    std::lock_guard<std::mutex> lock(mtx);
    // 2. Deposit the money.
    balance += amount;
    // 3. Print the updated balance.
    std::cout << "\nbalance: " << balance;
    // 4. Unlock the mutex.
    // 5. Notify the waiting thread.
    cv.notify_one();
}

int main() {
    std::thread t1(withdrawMoney, 500);
    std::thread t2(addMoney, 500);

    // TODO: Join both threads.
    t1.join();
    t2.join();

    std::cout << "\nFinal balance: " << balance;

    return 0;
}