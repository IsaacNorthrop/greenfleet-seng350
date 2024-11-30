#include <stdio.h>
#include <string>

class updateCommand {
    public:
        virtual ~updateCommand() = default;
        virtual void execute() const = 0;
};