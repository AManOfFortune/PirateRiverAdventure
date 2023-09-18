#pragma once

#include <utility>

/// <summary>
/// This class handles user input polling and should only be instantiated once.
/// </summary>
class Input
{
public:
    static bool IsKeyPressed(int key);
    static bool IsMouseButtonPressed(int button);
    static std::pair<float, float> MousePosition();
    static float MouseX();
    static float MouseY();

private:
    static Input* instance_;
};