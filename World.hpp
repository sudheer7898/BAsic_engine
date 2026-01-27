#pragma once
class GameObject; 
#include <vector>
#include <memory>

static std::vector<std::shared_ptr<GameObject>> g_World = {};
