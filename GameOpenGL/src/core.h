#pragma once

#ifdef ENABLE_ASSERT
    #define ASSERT(x, ...) { if (!(x)) {  LOG_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define ASSERT(x, ...)
#endif  // ENABLE_ASSERT

#define BIT(x) (1 << x)