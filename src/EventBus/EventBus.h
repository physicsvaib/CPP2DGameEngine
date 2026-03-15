#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"

class EventBus
{
  public:
    EventBus()
    {
        Logger::Log("Event Bus Created");
    }
    ~EventBus()
    {
        Logger::Log("Event Bus Destroyed");
    }
};

#endif