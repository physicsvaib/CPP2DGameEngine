#ifndef HANDLERLIST_H
#define HANDLERLIST_H

#include "Event.h"

class IEventCallback
{
  private:
    virtual void Call(Event& e) = 0;

  public:
    virtual ~IEventCallback() = default;
    void Execute(Event& e)
    {
        Call(e);
    }
};

template <typename TOwner, typename TEvent> class EventCallback : public IEventCallback
{
  private:
    using CallbackFunction = void (TOwner::*)(TEvent&);
    TOwner* ownerInstance;
    CallbackFunction callbackFunction;

    virtual void Call(Event& e) override
    {
        std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
    }

  public:
    EventCallback(TOwner owner, CallbackFunction callback)
    {
        ownerInstance = owner;
        callbackFunction = callback;
    }

    virtual ~EventCallback override = default;
};

#endif