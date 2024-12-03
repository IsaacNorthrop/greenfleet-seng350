#include <stdio.h>
#include <string>
#include "../commands/updateCommand.h"

using namespace std;

class PaymentInfo {
    public:
        string paymentType;
        string credentials;
};

class Customer {
    public:
        string name;
        string password;
        string address;
        string destination;
        bool share;
        PaymentInfo customerPaymentInfo;
        int ecoPoints;
        updateCommand updateHeartbeat();
        updateCommand updatePoints();

};

