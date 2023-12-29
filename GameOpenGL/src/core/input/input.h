#pragma once

#include <memory>
#include <utility>

/// <summary>
/// This class handles user input polling and should only be instantiated once.
/// </summary>
class Input
{
public:
    Input() = default;

    static bool IsKeyPressed(int key);
    static bool IsMouseButtonPressed(int button);
    static std::pair<float, float> MousePosition();
    static float MouseX();
    static float MouseY();
protected:
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

private:
    static std::unique_ptr<Input> instance_;
};