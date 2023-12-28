#pragma once

#include "event.h"

#include <sstream>

/// <summary>
/// This class represents an event that is triggered when the window is resized.
/// </summary>
class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height) : width_(width), height_(height) {}

    std::string ToString() const override 
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << width_ << ", " << height_;
        return ss.str();
    }

    inline unsigned int width() const { return width_; }
    inline unsigned int height() const { return height_; }

    // Instead of manual implementation of method overrides.
    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kWindowResize)

private:
    unsigned int width_, height_;
};

/// <summary>
/// This class represents an event that is triggered when the window close button is pressed.
/// </summary>
class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() = default;

    // Instead of manual implementation of method overrides.
    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kWindowClose)
};


class AppTickEvent : public Event
{
public:
    AppTickEvent() = default;

    // Instead of manual implementation of method overrides.
    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kAppTick)
};

class AppUpdateEvent : public Event
{
public:
    AppUpdateEvent() = default;

    // Instead of manual implementation of method overrides.
    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kAppUpdate)
};

class AppRenderEvent : public Event
{
public:
    AppRenderEvent() = default;

    // Instead of manual implementation of method overrides.
    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kAppRender)
};