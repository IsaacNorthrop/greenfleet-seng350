#include <iostream>
#include <string>
#include "notificationStrategy.h"

using namespace std;

void EmailStrategy::notify(string message) const {
    cout << "Sending email notification... " << message << endl;
}

void SMSStrategy::notify(string message) const {
    cout << "Sending SMS notification... " << message << endl;
}

void PhoneStrategy::notify(string message) const {
    cout << "Making phone call notification... " << message << endl;
}

NotificationContext::NotificationContext(NotificationStrategy* strat)
    : strategy(strat) {}

void NotificationContext::setStrategy(NotificationStrategy* strat) {
    strategy = strat;
}

void NotificationContext::executeNotification(string message) const {
    strategy->notify(message);
}