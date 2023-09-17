#include "layer_stack.h"

LayerStack::LayerStack() 
{
    layer_insert_ = layers_.begin();
}

LayerStack::~LayerStack() 
{
    for (Layer* layer : layers_) 
    { 
        delete layer; 
    }
}

void LayerStack::PushLayer(Layer* layer) 
{
    layer_insert_ = layers_.emplace(layer_insert_, layer);
}

void LayerStack::PopLayer(Layer* layer) 
{
    auto iterator = std::find(layers_.begin(), layers_.end(), layer);
    if (iterator != layers_.end()) 
    {
        layers_.erase(iterator);
        layer_insert_--;
    }
}

void LayerStack::PushOverlay(Layer* overlay) 
{
    layers_.emplace_back(overlay);
}

void LayerStack::PopOverlay(Layer* overlay) 
{
    auto iterator = std::find(layers_.begin(), layers_.end(), overlay);
    if (iterator != layers_.end())
    {
        layers_.erase(iterator);
    }
}