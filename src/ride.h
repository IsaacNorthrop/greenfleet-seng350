#include <stdio.h>
#include <string>

using namespace std;

class Ride {
    public:
        string driverName;
        string licensePlate;
        string carDescription;
        int capacity;
        bool rideShare;
        bool servingCustomer;
        bool updateHeartbeat();
    
};