#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <string>
class Notification {
public:
    static std::string sendReminder(std::string message);
};
#endif