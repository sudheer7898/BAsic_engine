#include <glad/glad.h>
#include "engine.hpp"
#include"input/input.hpp"
#include <iostream>
#include <chrono>
#include <thread>

// Static helper to handle GLFW startup
void Engine::InitializeGLFW() {
    static bool initialized = false;
    if (!initialized) {
        if (!glfwInit()) {
            std::cerr << "GLFW init failed\n";
            std::exit(-1);
        }
        initialized = true;
    }
}

// Constructor using Initializer List to fix C2280
Engine::Engine(int width, int height, const char* title)
    : m_window((InitializeGLFW(), width), height, title)
{
    // Configure OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window.makeCurrent(); // Sets GEngine().window

    // Load OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD init failed\n";
        std::exit(-1);
    }

    // Initialize the Input system callbacks
    Input::Init();
}

Engine::~Engine() {
    glfwTerminate();
}

void Engine::run(Window& window) {
    window.makeCurrent();

    EngineContext& ctx = GEngine();
    ctx.frameRate = (ctx.frameRate > 0) ? ctx.frameRate : 60;

    const double targetFrameTime = 1.0 / ctx.frameRate;
    using clock = std::chrono::steady_clock;
    auto lastTime = clock::now();
    GLFWwindow* typecastWindow = ctx.window;
    while (!window.windowCloseStatus()) {
        if (show_frameRate) DebugFPS();
        auto now = clock::now();
        std::chrono::duration<double> frameTime = now - lastTime;
        lastTime = now;
        ctx.deltaTime = frameTime.count();
        // Standard rendering setup
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Swap buffers and Poll Events
        window.update();

        // Frame limiting logic
        if (ctx.deltaTime < targetFrameTime) {
            std::this_thread::sleep_for(
                std::chrono::duration<double>(targetFrameTime - ctx.deltaTime)
            );
        }
    }
}

void Engine::setFramerate(int frameRate) {
    GEngine().frameRate = frameRate;
}

void Engine::Show_frameRates() {
    show_frameRate = true;
}

void Engine::DebugFPS() {
    static double acc = 0.0;
    static int frames = 0;

    acc += GEngine().deltaTime;
    frames++;

    if (acc >= 1.0) {
        std::cout << "FPS: " << frames << "\n";
        acc = 0.0;
        frames = 0;
    }
}

Window& Engine::getNativeWindow() {
    return m_window;
}