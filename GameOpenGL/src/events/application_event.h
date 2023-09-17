#pragma once

#include "event.h"

#include <sstream>

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

    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kWindowResize)

private:
    unsigned int width_, height_;
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}

    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kWindowClose)
};

class AppTickEvent : public Event
{
public:
    AppTickEvent() {}

    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kAppTick)
};

class AppUpdateEvent : public Event
{
public:
    AppUpdateEvent() {}

    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kAppUpdate)
};

class AppRenderEvent : public Event
{
public:
    AppRenderEvent() {}

    EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    EVENT_CLASS_TYPE(kAppRender)
};