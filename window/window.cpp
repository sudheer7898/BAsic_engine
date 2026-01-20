#include "window.hpp"

Window::Window(int width, int height, const char* title) {
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    GEngine().width = width;
    GEngine().height = height;
    glfwSetFramebufferSizeCallback(m_window, framebufferCallback);
}

Window::~Window() {
    if (m_window)
        glfwDestroyWindow(m_window);
}

void Window::makeCurrent() {
    glfwMakeContextCurrent(m_window);
    GEngine().window = m_window;
}

void Window::update() {
    glClearColor(windowColor[0], windowColor[1], windowColor[2], windowColor[3]);
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Window::shouldClose() const {
    glfwSetWindowShouldClose(m_window, true);
}

bool Window::windowCloseStatus() const
{
    return glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::nativeHandle() const {
    return m_window;
}

void Window::setColor(float Color[],int n) {
    if (n == 4) {
        windowColor[0] = Color[0];
        windowColor[1] = Color[1];
        windowColor[2] = Color[2];
        windowColor[3] = Color[3];
    }
    else if (n == 3) {
        windowColor[0] = Color[0];
        windowColor[1] = Color[1];
        windowColor[2] = Color[2];
    }
    else {
        std::cout << "Cannot set the color due to invalid arguments"<<std::endl;
    }
}

float* Window::returnColor(){
    return windowColor;
}

void Window::framebufferCallback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}
