#pragma once

#include "events/event.h"

#include <string>

/// <summary>
/// This class represents a single layer that is part of the applications layer stack.
/// </summary>
class Layer 
{
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer() = default;

    /// <summary>
    /// This callback method is invoked when the layer is pushed onto the application layer stack.
    /// </summary>
    virtual void OnAttach() {}
    /// <summary>
    /// This callback method is invoked when the layer is popped from the application layer stack.
    /// </summary>
    virtual void OnDetach() {}
    /// <summary>
    /// This callback method is invoked during the applications OnUpdate method.
    /// </summary>
    virtual void OnUpdate() {}
    /// <summary>
    /// This method is called when an event is propagated from the layer stack to this layer.
    /// </summary>
    /// <param name="event"></param>
    virtual void OnEvent(Event& event) {}

    inline const std::string name() const { return debug_name_; }

protected:
    std::string debug_name_;
};

