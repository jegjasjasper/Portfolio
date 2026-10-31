
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

int inventory = 1000;
int totalSold = 0;
int totalRestocked = 0;

std::mutex inventoryMutex;

void sellProducts(int quantity, int repetitions) {
    for (int i = 0; i < repetitions; i++) {
        // TODO:
        // 1. Lock the mutex.
        inventoryMutex.lock();
        // 2. Check whether enough inventory exists.
        if(inventory > 0){
        // 3. If enough, update inventory and totalSold.
        inventory -= quantity;
        totalSold += quantity;
        }
        // 4. Unlock the mutex.
        inventoryMutex.unlock();
    }
}

void restockProducts(int quantity, int repetitions) {
    for (int i = 0; i < repetitions; i++) {
        // TODO:
        // 1. Lock the mutex.
        inventoryMutex.lock();
        // 2. Increase inventory.
	inventory += quantity;
        // 3. Update totalRestocked.
        totalRestocked += quantity;
        // 4. Unlock the mutex.
        inventoryMutex.unlock();
    }
}

int main() {
    // TODO: Create two selling threads and two restocking threads.
    std::thread SP1(sellProducts, 2, 200);
    std::thread SP2(sellProducts, 2, 200);
    std::thread RP1(restockProducts, 3, 150);
    std::thread RP2(restockProducts, 3, 150);

    // TODO: Join all four threads.
    SP1.join();
    SP2.join();
    RP1.join();
    RP2.join();
    

    std::cout << "Inventory: " << inventory << '\n';
    std::cout << "Total sold: " << totalSold << '\n';
    std::cout << "Total restocked: " << totalRestocked << '\n';

    return 0;
}
