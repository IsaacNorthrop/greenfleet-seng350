#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include "customer.h"

using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;

void driverThread()
{
    string name;
    string password;

    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []
            { return ready; });

    cout << "Driver Login: " << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "Password: ";
    getline(cin, password);

    {
        lock_guard lock(mtx);
        ready = true;
    }

    cv.notify_one();

    cout << "Thread A is running\n";
}

void customerThread()
{
    string input;
    string address;
    Customer customer;

    cout << "Customer Login: " << endl;
    cout << "Name: ";
    getline(cin, customer.name);
    cout << "Password: ";
    getline(cin, customer.password);
    cout << "Welcome to Green Fleet, " + customer.name + "!"<< endl;
    while(true){
        cout << "Would you like to hail a ride? (y/n) ";
        getline(cin, input);
        if(input == "y")
            break;
    }

    {
        lock_guard lock(mtx);
        ready = true;
    }

    cv.notify_one();

    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []
            { return ready; });
}

int main()
{
    thread customer(customerThread);
    thread driver(driverThread);

    driver.join();
    customer.join();

    return 0;
}
