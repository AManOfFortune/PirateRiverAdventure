#pragma once

class DeltaTime
{
public:
    DeltaTime(float time = 0.0f)
        : time_(time)
    { }

    // This operator overload allows this class to be cast (implicitly and explicitly) into a float for convenience.
    // This cast returns the delta time in seconds.
    operator float() const { return time_; }

    float seconds() const { return time_; }
    float milliseconds() const { return time_ * 1000.0f; }

private:
    // Time in seconds.
    float time_;
};