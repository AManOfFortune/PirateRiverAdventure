#pragma once

#include "core.h"

#include <functional>
#include <iostream>

enum class EventType 
{
    kNone = 0,
    kWindowClose, kWindowResize, kWindowFocus, kWindowLostFocus, kWindowMoved,
    kAppTick, kAppUpdate, kAppRender,
    kKeyPressed, kKeyReleased,
    kMouseButtonPressed, kMouseButtonReleased, kMouseMoved, kMouseScrolled
};

enum EventCategory 
{
    kNone = 0,
    kEventCategoryApplication = BIT(0),
    kEventCategoryInput = BIT(1),
    kEventCategoryKeyboard = BIT(2),
    kEventCategoryMouse = BIT(3),
    kEventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_CATEGORY(category) virtual int category_flags() const override { return category; }

#define EVENT_CLASS_TYPE(type) static EventType GetType() { return EventType::##type; }\
								virtual EventType event_type() const override { return GetType(); }\
								virtual const char* name() const override { return #type; }

class Event
{
    friend class EventDispatcher;
public:
    inline bool IsInCategory(EventCategory category) const { return category_flags() & category; }
    inline bool IsHandled() const { return is_handled_; }
    virtual std::string ToString() const { return name(); }

    virtual int category_flags() const = 0;
    virtual const char* name() const = 0;
    virtual EventType event_type() const = 0;

protected:
    bool is_handled_ = false;
};

class EventDispatcher
{
    template <typename T>
    using EventFn = std::function<bool(T&)>;
public:
    EventDispatcher(Event& event) : event_(event) {}

    template <typename T>
    bool Dispatch(EventFn<T> func)
    {
        if (event_.event_type() == T::GetType())
        {
            event_.is_handled_ = func(*(T*)&event_);

            return true;
        }

        return false;
    }

private:
    Event& event_;
};

inline std::ostream& operator<<(std::ostream& os, const Event& event)
{
    return os << event.ToString();
}