// engine_context.hpp
#pragma once
#include"Scene/scene.hpp"
struct GLFWwindow;
class Camera3D;
struct EngineContext {
    GLFWwindow* window = nullptr;
    int width = 0;
    int height = 0;
    int frameRate = 60;
    double deltaTime = 0.0;
    std::vector<std::shared_ptr<Scene>> scenes = { std::make_shared<Scene>("DefaultScene") };
    Scene* activeScene = scenes[0].get();
    std::shared_ptr<Camera3D> activeCamera=nullptr;
};

EngineContext& GEngine();