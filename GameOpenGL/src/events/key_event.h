#pragma once

#include "event.h"

#include <sstream>

class KeyEvent : public Event 
{
public:
    inline int key_code() const { return key_code_; }

    EVENT_CLASS_CATEGORY(kEventCategoryKeyboard | kEventCategoryInput)

protected:
    KeyEvent(int code) : key_code_(code) {}

    int key_code_;
};

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

    EVENT_CLASS_TYPE(kKeyPressed)

private:
    int repeat_count_;
};

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

    EVENT_CLASS_TYPE(kKeyReleased)
};