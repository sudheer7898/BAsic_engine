#pragma once
#include"../engine_state.hpp"
#include <GLFW/glfw3.h>
#include<iostream>


class Window {
public:
    Window() = default;
    Window(int width, int height, const char* title);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    void makeCurrent();
    void update();
    void shouldClose() const;
    bool windowCloseStatus() const;
    GLFWwindow* nativeHandle() const;
    void setColor(float Color[],int n);
    float* returnColor();

private:
    GLFWwindow* m_window = nullptr;
    float windowColor[4] = {0.0f,0.0f,0.0f,1.0f};
    static void framebufferCallback(GLFWwindow* window, int width, int height);
};
