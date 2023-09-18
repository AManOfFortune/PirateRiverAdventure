#pragma once

#include "layer.h"

#include <vector>

/// <summary>
/// A layer stack is a class that consists of multiple layers/overlays.
/// This class is created so that lower layers can be rendered before the
/// upper layers and overlays. Events are propagated in reverse order, if an
/// event is handled by a layer/overlay it is not passed onto the lower layers.
/// </summary>
class LayerStack 
{
public:
    LayerStack();
    ~LayerStack();

    /// <summary>
    /// Pushes the layer onto the layer stack.
    /// </summary>
    void PushLayer(Layer* layer);
    /// <summary>
    /// Pops the layer from the layer stack.
    /// </summary>
    void PopLayer(Layer* layer);
    /// <summary>
    /// Pushes the overlay onto the layer stack. An overlay is the same as a layer,
    /// the only difference is that an overlay will always be pushed on top of layers.
    /// </summary>
    void PushOverlay(Layer* overlay);
    /// <summary>
    /// Pops the overlay from the layer stack.
    /// </summary>
    void PopOverlay(Layer* overlay);

    // Getters for the layer stack iterators and reverse iterators.
    std::vector<Layer*>::iterator begin() { return layers_.begin(); }
    std::vector<Layer*>::iterator end() { return layers_.end(); }
    std::vector<Layer*>::reverse_iterator rbegin() { return layers_.rbegin(); }
    std::vector<Layer*>::reverse_iterator rend() { return layers_.rend(); }

private:
    std::vector<Layer*> layers_;
    // This unsigned int tracks the position that layers are inserted in.
    // This way the layers are always inserted before any overlays.
    unsigned int layer_insert_index_ = 0;
};