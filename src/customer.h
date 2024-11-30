#include <stdio.h>
#include <string>

using namespace std;

class Customer {
    public:
        string name;
        PaymentInfo customerPaymentInfo;
        int ecoPoints;
        bool updateHeartbeat();
        bool updatePoints();

};

class PaymentInfo {
    public:
        string paymentType;
        string credentials;
};