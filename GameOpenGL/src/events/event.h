#pragma once

#include "utils.h"


#include <functional>
#include <sstream>
#include <string>

/// <summary>
/// Holds all possible event types that are triggered in our application.
/// </summary>
enum class EventType 
{
    kNone = 0,
    kWindowClose, kWindowResize, kWindowFocus, kWindowLostFocus, kWindowMoved,
    kAppTick, kAppUpdate, kAppRender,
    kKeyPressed, kKeyReleased, kKeyTyped,
    kMouseButtonPressed, kMouseButtonReleased, kMouseMoved, kMouseScrolled
};

/// <summary>
/// Holds all possible event categories that events can be part of. An event can be part of 
/// more than one category. The enum values are defined as a bitfield that way an Event class
/// can be assigned to multiple event categories by using the | (bitwise OR) operator.
/// </summary>
enum EventCategory 
{
    kNone = 0,
    kEventCategoryApplication = BIT(0),
    kEventCategoryInput = BIT(1),
    kEventCategoryKeyboard = BIT(2),
    kEventCategoryMouse = BIT(3),
    kEventCategoryMouseButton = BIT(4)
};

// The following two macros were used by TheCherno so that he didn't have to override the base class methods in every class.
#define EVENT_CLASS_CATEGORY(category) virtual int category_flags() const override { return category; }

#define EVENT_CLASS_TYPE(type) static EventType GetType() { return EventType::##type; }\
								virtual EventType event_type() const override { return GetType(); }\
								virtual const char* name() const override { return #type; }

/// <summary>
/// This is the base event class that all other event classes inherit from.
/// </summary>
class Event
{
    // The event dispatcher is defined as friend so that it has access to 
    // the protected is_handled_ member variable.
    friend class EventDispatcher;
public:
    /// <summary>
    /// Checks whether or not the event is in specified category. This is done using
    /// the & (bitwise AND) operator. The result of this bitwise operation is an integer
    /// which is implicitly cast to a boolean. 
    /// </summary>
    inline bool IsInCategory(EventCategory category) const { return category_flags() & category; }
    inline bool IsHandled() const { return is_handled_; }
    virtual std::string ToString() const { return name(); }

    // Specifies to which event categories the event belongs by returning an integer that is used as a bitfield.
    virtual int category_flags() const = 0;
    virtual const char* name() const = 0;
    virtual EventType event_type() const = 0;

protected:
    bool is_handled_ = false;
};

/// <summary>
/// This class is used to dispatch triggered events to the right callback function.
/// </summary>
class EventDispatcher
{
public:
    EventDispatcher(Event& event) : event_(event) {}

    /// <summary>
    /// This generic method takes in a generic TFunc& to which the event 
    /// of type T is passed. Returns true if the event was dispatched, false if not.
    /// </summary>
    template <typename T, typename TFunc>
    bool Dispatch(const TFunc& func)
    {
        // The event is only handled if the type of event this instance 
        // of EventDispatcher was instantiated with matches the generic type T.
        if (event_.event_type() == T::GetType())
        {
            // Cast is necessary for the compiler to know which version of the event to use.
            event_.is_handled_ = func(static_cast<T&>(event_));
            // Return true if dispatched (dispatched != handled successfully).
            return true;
        }

        // Return false if not dispatched.
        return false;
    }

private:
    Event& event_;
};

// Overriding the << operator so that events can be logged.
inline std::ostream& operator<<(std::ostream& os, const Event& event)
{
    return os << event.ToString();
}