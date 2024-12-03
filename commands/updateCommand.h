#include <stdio.h>
#include <string>

class Customer;
class Ride;

class updateCommand
{
public:
    virtual ~updateCommand() = default;
    virtual void execute() const = 0;
};

class updateEcoPointsCommand : public updateCommand
{
private:
    Customer &customer;
    int points;

public:
    updateEcoPointsCommand(Customer &customer, int points)
        : customer(customer), points(points) {}

    void execute() const override;
};

class updateAddressCommand : public updateCommand
{
private:
    Customer &customer;
    Ride &ride;

public:
    updateAddressCommand(Customer &customer, Ride &ride)
        : customer(customer), ride(ride) {}

    void execute() const override;
};