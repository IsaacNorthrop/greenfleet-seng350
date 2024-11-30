#include <stdio.h>
#include <string>


class NotificationStrategy {
    public:
        virtual ~NotificationStrategy() = default;
        virtual void notify() const = 0;
};

class EmailStrategy : NotificationStrategy {
    public:
        void notify() const override;
};

class SMSStrategy : NotificationStrategy {
    public:
        void notify() const override;
};

class PhoneStrategy : NotificationStrategy {
    public:
        void notify() const override;
};