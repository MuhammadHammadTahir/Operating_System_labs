#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <queue>

// Declare Snack enum before using it
enum class Snack { Popcorn, Soda, Candy };

std::mutex mtx;
std::condition_variable cv;
std::queue<Snack> orders;
bool done = false;

void prepareSnack(Snack snack) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return !orders.empty() || done; });

        if (done && orders.empty()) break;

        if (!orders.empty() && orders.front() == snack) {
            orders.pop();
            lock.unlock();

            std::cout << "Preparing " << (snack == Snack::Popcorn ? "Popcorn" : snack == Snack::Soda ? "Soda" : "Candy") << std::endl;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 5);
            std::this_thread::sleep_for(std::chrono::seconds(dis(gen)));
            std::cout << (snack == Snack::Popcorn ? "Popcorn" : snack == Snack::Soda ? "Soda" : "Candy") << " is ready!" << std::endl;
            
            cv.notify_all();
        }
    }
}

void takeOrder() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);

    for (int i = 0; i < 10; ++i) { // Take 10 orders for example
        Snack snack = static_cast<Snack>(dis(gen));
        {
            std::lock_guard<std::mutex> lock(mtx);
            orders.push(snack);
        }
        std::cout << "Ordered " << (snack == Snack::Popcorn ? "Popcorn" : snack == Snack::Soda ? "Soda" : "Candy") << std::endl;
        cv.notify_all();
        
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();
}

int main() {
    std::thread orderThread(takeOrder);
    std::thread popcornThread(prepareSnack, Snack::Popcorn);
    std::thread sodaThread(prepareSnack, Snack::Soda);
    std::thread candyThread(prepareSnack, Snack::Candy);

    orderThread.join();
    popcornThread.join();
    sodaThread.join();
    candyThread.join();

    return 0;
}
