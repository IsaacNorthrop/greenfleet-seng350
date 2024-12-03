#include <iostream>
#include <string>
#include "../src/Customer.h"
#include "../src/Ride.h"

void updateEcoPointsCommand::execute() const {
    customer.ecoPoints += points;
    cout << "Congratulations! You earned " << points << " points!" << endl;
}

void updateAddressCommand::execute() const {
    ride.destination = customer.destination;
}