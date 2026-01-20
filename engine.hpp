#pragma once
#include "shader/Shader_class.hpp"
#include "window/window.hpp"
#include "engine_state.hpp"
#include "input/input.hpp"

class Engine {
public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void run(Window& window);

    // Prevent copying to avoid multiple glfwTerminate calls
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    void setFramerate(int frameRate);
    void Show_frameRates();
    void DebugFPS();
    Window& getNativeWindow();

private:
    // Helper to ensure GLFW is ready before the Window member is constructed
    static void InitializeGLFW();

    double m_deltaTime = 0.0;
    bool show_frameRate = false;
    Window m_window; // Initialized via the constructor list
};