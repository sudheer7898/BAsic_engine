#include "input.hpp"
#include <unordered_map>

struct InputLayer {
    std::unordered_map<int, std::function<void()>> keyMap;
    std::unordered_map<int, std::function<void()>> mouseMap;
};

static float smoothedX = 0.0f;
static float smoothedY = 0.0f;

static std::vector<InputLayer> layers;
static int currentLayer = 0;

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS && !layers.empty()) {
        auto& m_map = layers[currentLayer].mouseMap;
        if (m_map.count(button)) {
            m_map[button]();
        }
    }
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && !layers.empty()) {
        auto& k_map = layers[currentLayer].keyMap;
        if (k_map.count(key)) {
            k_map[key]();
        }
    }
}

static void screenToNDC(GLFWwindow* window, double xpos, double ypos,float &ndcx,float &ndcy ) {
    int width = GEngine().width;
    int height = GEngine().height;
    ndcx = static_cast<float>((xpos / width) * 2.0 - 1.0);
    ndcy = static_cast<float>(1.0 - (ypos / height) * 2.0);
}

namespace Input {
    void Init() {
        AddLayer();

        GLFWwindow* window = GEngine().window;
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetKeyCallback(window, KeyCallback);
    }

    void AddLayer() {
        layers.push_back(InputLayer());
    }

    void SwitchLayer(int LayerNum) {
        if (LayerNum >= 0 && LayerNum < layers.size()) {
            currentLayer = LayerNum;
        }
        else{
            std::cerr << "not a valid number for Layer num";
        }
    }

    void SetMouseClickCallback(MouseInputType button, std::function<void()> callback) {
        if (!layers.empty()) {
            layers[currentLayer].mouseMap[(int)button] = callback;
        }
    }

    void SetKeyboardCallback(int key, std::function<void()> callback) {
        if (!layers.empty()) {
            layers[currentLayer].keyMap[key] = callback;
        }
    }

    void SetKeyboardCallback(KeyType key, std::function<void()> callback) {
        SetKeyboardCallback((int)key, callback);
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


    void getMousePos(float& x, float& y){
        GLFWwindow* window = GEngine().window;
        double sx, sy;
        glfwGetCursorPos(window, &sx, &sy);
        screenToNDC(window, sx, sy, x, y);
    }
    void UpdateSmoothing(float weight) {
        float rawX, rawY;
        getMousePos(rawX, rawY); 

        smoothedX += (rawX - smoothedX) * weight;
        smoothedY += (rawY - smoothedY) * weight;
    }

    void GetSmoothedMousePos(float& x, float& y) {
        x = smoothedX;
        y = smoothedY;
    }
}