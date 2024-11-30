#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <string>

std::string shared_data = "";
std::mutex mtx;

void customerThread(){

    // Simulate some data processing
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    {
        // Lock the mutex to safely update the shared data
        std::lock_guard<std::mutex> lock(mtx);
        shared_data = "Data from Terminal 1: Hello!";
    }

    // Display in Terminal 1
    std::system("cmd.exe /c start \"C:\Program Files\WindowsApps\Microsoft.WindowsTerminal_1.21.3231.0_x64__8wekyb3d8bbwe\wt.exe\" echo Hello World");
}

void driverThread(){

        // Simulate waiting for Terminal 1 data
    std::this_thread::sleep_for(std::chrono::seconds(2));

    {
        // Lock the mutex to safely read the shared data
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Terminal 2 received: " << shared_data << std::endl;
    }

    // Display in Terminal 2
    std::system("cmd.exe /c start \"C:\Program Files\WindowsApps\Microsoft.WindowsTerminal_1.21.3231.0_x64__8wekyb3d8bbwe\wt.exe\" echo Hello World");
}

int main() {

    std::thread t1(customerThread);
    std::thread t2(driverThread);

    t1.join();
    t2.join();

    std::cout << "Both terminals have completed their tasks." << std::endl;
    return 0;
}
