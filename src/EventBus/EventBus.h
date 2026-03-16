#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"
#include "HandlerList.h"
#include <list>
#include <map>
#include <memory>
#include <typeindex>

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus
{

  private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

  public:
    EventBus()
    {
        Logger::Log("Event Bus Created");
    }
    ~EventBus()
    {
        Logger::Log("Event Bus Destroyed");
    }

    template <typename TOwner, typename TEvent>
    void SubscribeToEvent(TOwner owner, void (TOwner::*FunctionCallack)(TEvent&))
    {
        // convert TOWner to type_index
        auto eventID = typeid(TEvent);
        if (!subscribers[eventID])
        {
            subscribers[eventID] = std::make_unique<HandlerList>();
        }

        auto sub = std::make_unique<EventCallback<TOwner, TEvent>>(owner, FunctionCallack);
        subscribers[eventID]->push_back(std::move(sub));
    }

    template <typename TEvent, typename... TArgs> void EmitEvent(TArgs&&... args)
    {
        auto handler = subscribers[typeid(TEvent)].get();
        if (!handler)
            return;

        for (auto it = handler->begin(); it != handler->end(); it++)
        {
            TEvent event(std::forward<TArgs>(args)...);
            it->get()->Execute(event);
        }
    }
};

#endif