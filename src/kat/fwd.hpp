#pragma once

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <entt/entt.hpp>
#include <eventpp/eventqueue.h>

#include <memory>
#include <typeindex>
#include <concepts>
#include <cinttypes>
#include <any>
#include <random>

namespace kat {
    class Engine;

    namespace event {
        struct BaseEvent {
            virtual ~BaseEvent() = default;
        };
    }
}