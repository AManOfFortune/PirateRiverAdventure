#pragma once

#include "event.h"

#include <sstream>

class MouseMovedEvent : public Event 
{
public:
    MouseMovedEvent(float x, float y) : mouse_x_(x), mouse_y_(y) {}

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << mouse_x_ << ", " << mouse_y_;
        return ss.str();
    }

    inline float mouse_x() const { return mouse_x_; }
    inline float mouse_y() const { return mouse_y_; }

    EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
    EVENT_CLASS_TYPE(kMouseMoved)

private:
    float mouse_x_, mouse_y_;
};

class MouseScrolledEvent : public Event 
{
public:
    MouseScrolledEvent(float xOffset, float yOffset) : x_offset_(xOffset), y_offset_(yOffset) {}

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << x_offset_ << ", " << y_offset_;
        return ss.str();
    }

    inline float x_offset() const { return x_offset_; }
    inline float y_offset() const { return y_offset_; }

    EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
    EVENT_CLASS_TYPE(kMouseScrolled)

private:
    float x_offset_, y_offset_;
};

class MouseButtonEvent : public Event 
{
public:
    inline int button() const { return button_; }

    EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)

protected:
    MouseButtonEvent(int button) : button_(button) {}

    int button_;
};

class MouseButtonPressedEvent : public MouseButtonEvent 
{
public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << button_;
        return ss.str();
    }

    EVENT_CLASS_TYPE(kMouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent 
{
public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << button_;
        return ss.str();
    }

    EVENT_CLASS_TYPE(kMouseButtonReleased)
};