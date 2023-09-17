#pragma once

#include "layer.h"

#include <vector>

class LayerStack 
{
public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PopLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopOverlay(Layer* overlay);

    std::vector<Layer*>::iterator begin() { return layers_.begin(); }
    std::vector<Layer*>::iterator end() { return layers_.end(); }
private:
    std::vector<Layer*> layers_;
    std::vector<Layer*>::iterator layer_insert_;
};