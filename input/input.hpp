#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include<iostream>
#include <vector>
#include "../engine_state.hpp"

enum class MouseInputType {
    Left = GLFW_MOUSE_BUTTON_LEFT,
    Right = GLFW_MOUSE_BUTTON_RIGHT
};

enum class KeyType {
    ESC=GLFW_KEY_ESCAPE,
    TAB=GLFW_KEY_TAB,
    LEFT_SHIFT=GLFW_KEY_LEFT_SHIFT,
    RIGHT_SHIFT=GLFW_KEY_RIGHT_SHIFT,
    LEFT_ARROW=GLFW_KEY_LEFT,
	RIGHT_ARROW = GLFW_KEY_RIGHT,
	UP_ARROW = GLFW_KEY_UP,
	DOWN_ARROW = GLFW_KEY_DOWN,
    PRT_SCR=GLFW_KEY_PRINT_SCREEN,
    SPACE=GLFW_KEY_SPACE,
    LEFT_ALT=GLFW_KEY_LEFT_ALT,
    RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
    LEFT_CTRL=GLFW_KEY_LEFT_CONTROL,
    RIGHT_CTRL = GLFW_KEY_RIGHT_CONTROL,
    ENTER=GLFW_KEY_ENTER
};

namespace Input {
    void Init();

    void AddLayer();

    void SwitchLayer(int LayerNum);

    void SetMouseClickCallback(MouseInputType button, std::function<void()> callback);

    // Overloaded: Version for standard ints (ASCII/GLFW_KEY_...)
    void SetKeyboardCallback(int key, std::function<void()> callback);

    // Overloaded: Version for your custom Enum
    void SetKeyboardCallback(KeyType key, std::function<void()> callback);

    bool IsKeyPressed(int key);

    void getMousePos(float& x,float& y);

    void UpdateSmoothing(float weight);

    void GetSmoothedMousePos(float& x, float& y);
}