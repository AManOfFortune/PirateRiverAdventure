#include "layer_stack.h"

LayerStack::LayerStack() 
{

}

LayerStack::~LayerStack() 
{
    // Layers are only deleted at the end of the applications lifetime.
    for (Layer* layer : layers_) 
    { 
        delete layer; 
    }
}

void LayerStack::PushLayer(Layer* layer) 
{
    // A new layer is always inserted at the position of the layer_insert_index_.
    // The layer_insert_index_ position is updated with the insertion.
    layers_.emplace(layers_.begin() + layer_insert_index_, layer);
    layer_insert_index_++;
    layer->OnAttach();
}

void LayerStack::PopLayer(Layer* layer) 
{
    auto iterator = std::find(layers_.begin(), layers_.begin() + layer_insert_index_, layer);
    if (iterator != layers_.end()) 
    {
        layer->OnDetach();
        layers_.erase(iterator);
        // Update the layer_insert_index_.
        layer_insert_index_--;
    }
}

void LayerStack::PushOverlay(Layer* overlay) 
{
    // Overlays are always pushed at the back of the layer stack.
    layers_.emplace_back(overlay);
    overlay->OnAttach();
}

void LayerStack::PopOverlay(Layer* overlay) 
{
    auto iterator = std::find(layers_.begin() + layer_insert_index_, layers_.end(), overlay);
    if (iterator != layers_.end())
    {
        overlay->OnDetach();
        layers_.erase(iterator);
    }
}