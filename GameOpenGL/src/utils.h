#pragma once

// This preprocessor definition is only defined in the Debug configuration.
#ifdef ENABLE_ASSERT
    // The ASSERT macro checks whether an expression is true or not 
    // and logs an error message should the assertion fail.
    #define ASSERT(x, ...) { if (!(x)) {  LOG_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define ASSERT(x, ...)
#endif  // ENABLE_ASSERT

// This is a helper macro to create bitfields.
#define BIT(x) (1 << x)