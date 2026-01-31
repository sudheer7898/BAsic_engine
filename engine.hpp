#pragma once
#include "shader/Shader_class.hpp"
#include "window/window.hpp"
#include "engine_state.hpp"
#include "input/input.hpp"
#include"Objects/gameObject.hpp"
#include"Scene/scene.hpp"
#include"render/renderer.hpp"

class Engine {
public:
    Engine() = default;
    Engine(int width, int height, const char* title);
    ~Engine();

    void run();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    void setFramerate(int frameRate);
    void Show_frameRates();
    void DebugFPS();
    Window& getNativeWindow();
    void PrintWorld();
    void setShaderPaths(const std::string& vertexPath, const std::string& fragmentPath);
    Scene* activeScene = GEngine().activeScene;
	
private:
    static void InitializeGLFW();

    double m_deltaTime = 0.0;
    bool show_frameRate = false;
    Window m_window;
    Renderer renderer;
    bool ShadersSet = false;
    std::shared_ptr<Shader_class> shaderProgram = nullptr;
};