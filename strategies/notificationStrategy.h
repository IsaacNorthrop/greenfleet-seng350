#include <string>

using namespace std;

class NotificationStrategy {
public:
    virtual ~NotificationStrategy() = default;
    virtual void notify(string message) const = 0;
};

class EmailStrategy : public NotificationStrategy {
public:
    void notify(string message) const override;
};

class SMSStrategy : public NotificationStrategy {
public:
    void notify(string message) const override;
};

class PhoneStrategy : public NotificationStrategy {
public:
    void notify(string message) const override;
};

class NotificationContext {
private:
    NotificationStrategy* strategy; 

public:
    NotificationContext(NotificationStrategy* strat);
    void setStrategy(NotificationStrategy* strat);
    void executeNotification(string message) const;
};
