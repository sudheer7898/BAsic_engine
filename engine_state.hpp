// engine_context.hpp
#pragma once
struct GLFWwindow;
struct EngineContext {
    GLFWwindow* window=nullptr;
    int width=0;
    int height=0;
    int frameRate=60;
    double deltaTime = 0.0;
};

EngineContext& GEngine();
