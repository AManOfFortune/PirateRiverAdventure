#pragma once

#include "events/event.h"

#include <string>

class Layer 
{
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnEvent(Event& event) {}

    inline const std::string name() const { return debug_name_; }

protected:
    std::string debug_name_;
};

