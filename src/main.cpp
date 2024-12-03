#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include "customer.h"
#include "ride.h"
#include "../strategies/notificationStrategy.h"

using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;
queue<Customer> customers;

void driverThread()
{
    string input;
    Ride ride;
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []
                { return ready; });
        ready = false;
    }
    cout << "Driver Login: " << endl;
    cout << "Name: ";
    getline(cin, ride.driverName);
    cout << "Password: ";
    getline(cin, ride.password);
    cout << "Enter your car's license plate: ";
    getline(cin, ride.licensePlate);
    cout << "Describe your car: ";
    getline(cin, ride.carDescription);
    cout << "How many passengers can you hold? ";
    getline(cin, ride.capacity);
    cout << "Thank you for driving with Green Fleet!" << endl;
    while (true)
    {
        cout << "Would you like to accept a ride? (y/n) ";
        getline(cin, input);
        if (input == "y")
            break;
    }
    Customer current = customers.front();
    updateAddressCommand getDestination(current, ride);
    getDestination.execute();

    while (true)
    {
        cout << "There is a customer at " << current.address << " going to " << ride.destination << ". would you like to accept? (y/n) ";
        getline(cin, input);
        if (input == "y")
            break;
    }
    customers.pop();

    EmailStrategy emailStrategy;
    SMSStrategy smsStrategy;
    PhoneStrategy phoneStrategy;

    NotificationContext context(&emailStrategy);
    context.executeNotification("Matched with " + ride.driverName);
    getline(cin, input);

    context.setStrategy(&smsStrategy);
    context.executeNotification("Matched with " + ride.driverName);
    getline(cin, input);

    context.setStrategy(&phoneStrategy);
    context.executeNotification("Matched with " + ride.driverName);
    getline(cin, input);

    while (true)
    {
        cout << "Have you picked up the customer? (y/n) ";
        getline(cin, input);
        if (input == "y")
            break;
    }

    {
        lock_guard lock(mtx);
        ready = true;
    }

    cv.notify_one();
    return;
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
    cout << "Welcome to Green Fleet, " + customer.name + "!" << endl;
    while (true)
    {
        cout << "Would you like to hail a ride? (y/n) ";
        getline(cin, input);
        if (input == "y")
            break;
    }
    cout << "Where are you located? (street, city, province) ";
    getline(cin, customer.address);
    cout << "Where would you like to go? (street, city, province) ";
    getline(cin, customer.destination);
    while (true)
    {
        cout << "Would you like to share your ride? By sharing, you can double the eco-points earned! (y/n) ";
        getline(cin, input);
        if (input == "y")
        {
            customer.share = true;
            break;
        }
        else if (input == "n")
        {
            customer.share = false;
            break;
        }
    }
    cout << "Connecting you with a driver!" << endl;
    customers.push(customer);
    {
        lock_guard lock(mtx);
        ready = true;
    }

    cv.notify_one();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []
                { return ready; });
        ready = false;
    }
    while (true)
    {
        cout << "Has the driver picked you up? (y/n) ";
        getline(cin, input);
        if (input == "y")
            break;
    }
    while (true)
    {
        cout << "Has the driver dropped you off? (y/n) ";
        getline(cin, input);
        if (input == "y")
            break;
    }
    if(customer.share){
        updateEcoPointsCommand updatePoints(customer, 100);
        updatePoints.execute();
    } else {        
        updateEcoPointsCommand updatePoints(customer, 50);
        updatePoints.execute();
    }

    cout << "Thank you for riding with Green Fleet!" << endl;
    return;
}

int main()
{
    thread customer(customerThread);
    thread driver(driverThread);

    driver.join();
    customer.join();

    return 0;
}
