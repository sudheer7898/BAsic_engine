#include "input.hpp"
#include<unordered_map>
#include<vector>
// Static storage for callbacks
static std::unordered_map<int, std::function<void()>> mouseCallbacks;
static std::vector<std::unordered_map<int,std::function<void()>>> layers;
static int currentLayer = 0;
// GLFW to Engine bridge
static void MouseButtonCallback(GLFWwindow* window,int button,int action,int mods){
    if (action == GLFW_PRESS) {
        auto it = mouseCallbacks.find(button);
        if (it != mouseCallbacks.end()) {
            it->second(); // call user callback
        }
    }
}
// 1. Corrected Map Name and Signature
static std::unordered_map<int, std::function<void()>> keyCallbacks;

// 2. Corrected Signature for Keyboard Keys
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        auto it = keyCallbacks.find(key);
        if (it != keyCallbacks.end()) {
            it->second();
        }
    }
}


namespace Input {
    void Init() {
        GLFWwindow* window = GEngine().window;
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetKeyCallback(window, KeyCallback);
    }    

    void SetMouseClickCallback(MouseInputType button,std::function<void()> callback){
        
        mouseCallbacks[(int)button] = callback;
    }
    void SetKeyboardCallback(int key, std::function<void()> callback) {
        keyCallbacks[key] = callback;
    }

    // Now uses the same name as above
    void SetKeyboardCallback(KeyType key, std::function<void()> callback) {
        keyCallbacks[(int)key] = callback;
    }
    bool IsKeyPressed(int key) {
        GLFWwindow* window = GEngine().window;
        if (!window) {
            std::cout << "Input Error: Window context is null\n";
            return false;
        }

        int state = glfwGetKey(window, key);
        return (state == GLFW_PRESS || state == GLFW_REPEAT);
    }
}