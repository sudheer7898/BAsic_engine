// engine_context.cpp
#include "engine_state.hpp"
#include<GLFW/glfw3.h>
EngineContext& GEngine() {
    static EngineContext ctx;
    return ctx;
}