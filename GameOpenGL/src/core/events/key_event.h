#pragma once

#include "event.h"

#include <sstream>

/// <summary>
/// This is the parent class of all key events.
/// </summary>
class KeyEvent : public Event 
{
public:
    inline int key_code() const { return key_code_; }

    // Instead of manual implementation of method overrides.
    EVENT_CLASS_CATEGORY(kEventCategoryKeyboard | kEventCategoryInput)

protected:
    KeyEvent(int code) : key_code_(code) {}

    int key_code_;
};

/// <summary>
/// This class represents an event when a key is pressed or held.
/// </summary>
class KeyPressedEvent : public KeyEvent 
{
public:
    KeyPressedEvent(int code, int repeat) : KeyEvent(code), repeat_count_(repeat) {}

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << key_code_ << " (" << repeat_count_ << " repeats)";
        return ss.str();
    }

    inline int repeat_count() const { return repeat_count_; }

    // Instead of manual implementation of method overrides.
    EVENT_CLASS_TYPE(kKeyPressed)

private:
    int repeat_count_;
};

/// <summary>
/// This class represents an event that is triggered when a key is released.
/// </summary>
class KeyReleasedEvent : public KeyEvent 
{
public:
    KeyReleasedEvent(int code) : KeyEvent(code) {}

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << key_code_;
        return ss.str();
    }

    // Instead of manual implementation of method overrides.
    EVENT_CLASS_TYPE(kKeyReleased)
};

/// <summary>
/// This class represents an event that is triggered when a character is typed.
/// </summary>
class KeyTypedEvent : public KeyEvent
{
public:
  KeyTypedEvent(int code) : KeyEvent(code) {}

  std::string ToString() const override
  {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << key_code_;
    return ss.str();
  }

  // Instead of manual implementation of method overrides.
  EVENT_CLASS_TYPE(kKeyTyped)
};