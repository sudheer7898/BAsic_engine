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
void Engine::run() {
    Window& window = Engine::getNativeWindow();
    EngineContext& ctx = GEngine();

    const double targetFrameTime = 1.0 / ctx.frameRate;
    using clock = std::chrono::steady_clock;
    auto lastTime = clock::now();
    shaderProgram->use();

    while (!window.windowCloseStatus()) {
        // 1. Calculate Delta Time
        auto now = clock::now();
        std::chrono::duration<double> frameTime = now - lastTime;
        lastTime = now;
        ctx.deltaTime = frameTime.count();

        // 2. Clear Buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark grey background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 3. DRAWING LOGIC MUST BE HERE
        if (shaderProgram && ctx.activeScene) {
            renderer.renderScene(*ctx.activeScene);
        }

        // 4. Swap buffers and Poll Events
        window.update();

        // Frame limiting
        if (ctx.deltaTime < targetFrameTime) {
            std::this_thread::sleep_for(std::chrono::duration<double>(targetFrameTime - ctx.deltaTime));
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

void Engine::PrintWorld() {
	int num_scenes = static_cast<int>(GEngine().scenes.size());
    std::cout << "--- World Hierarchy (" << num_scenes << " scenes) ---" << std::endl;
    for(int i=0;i<num_scenes;i++){
        std::cout<<"Scene "<<i+1<<": "<<GEngine().scenes[i]->getName()<<std::endl;
    int size = GEngine().scenes[i]->getSize();
    std::cout << "--- Scene Hierarchy (" << size << " objects) ---" << std::endl;

    if (GEngine().scenes[i]->getSize() == 0) {
        std::cout << "Scene " << GEngine().scenes[i]->getName() << " is empty." << std::endl;
        return;
    }   

    for (const auto& obj : GEngine().scenes[i]->getAllObjects()) {
        if (obj) {
            std::cout << "[ID: " << obj->m_id << "] Name: " << obj->m_name << std::endl;
            std::vector<float> data = obj->getInterLeavedData();
            std::cout << "vertices:" << std::endl;
            for (size_t j = 0; j < data.size(); j += 6) {
                std::cout << "Position: (" << data[j] << ", " << data[j + 1] << ", " << data[j + 2] << "), "
                          << "Color: (" << data[j + 3] << ", " << data[j + 4] << ", " << data[j + 5] << ")" << std::endl;
			}
        }
        else {
            std::cout << "[Warning]: Null pointer found in g_World!" << std::endl;
        }
    }
    std::cout << "------------------------------------------" << std::endl;
	}
}

void Engine::setShaderPaths(const std::string& vertexPath, const std::string& fragmentPath)
{
	shaderProgram=std::make_shared<Shader_class>(vertexPath.c_str(), fragmentPath.c_str());
    ShadersSet = true;
}
