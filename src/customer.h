#include <stdio.h>
#include <string>

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
        PaymentInfo customerPaymentInfo;
        int ecoPoints;
        bool updateHeartbeat();
        bool updatePoints();

};

