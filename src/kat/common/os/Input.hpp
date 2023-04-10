#pragma once

#include "kat/common/os/Window.hpp"

namespace kat::os::input {
    enum class Key {
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        Numpad0, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
        NumpadMinus, NumpadPlus, NumpadDivide, NumpadMultiply, NumpadEnter, NumpadEqual,
        Grave, Minus, Equals, LeftBracket, RightBracket, Backslash,
        Semicolon, Apostraphe, Comma, Period, ForwardSlash,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
        F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
        Home, Insert, PageUp, PageDown, End, Pause, PrintScreen, Delete,
        LeftControl, RightControl,
        LeftShift, RightShift,
        LeftAlt, RightAlt,
        LeftSuper, RightSuper,
        CapsLock, Tab, Enter, NumLock, ScrollLock, Backspace, Menu,
        World1, World2,
    };

    enum class Button {
        Left, Middle, Right
    };

    enum class GamepadAxis {
        LeftX, LeftY, RightX, RightY,
        LeftTrigger, RightTrigger
    };

    enum class GamepadButton {
        A, B, X, Y,
        LeftBumper, RightBumper,
        Back, Start, Guide,
        LeftThumb, RightThumb,
        DpadUp, DpadRight, DpadDown, DpadLeft,

        // PS Controller Names
        Cross = A,
        Circle = B,
        Square = X,
        Triangle = Y
    };

    struct JoystickHatState {

        /**
         * X < 0: Left           X == 0: Centered          X > 0: Right
         * Y < 0: Down           Y == 0: Centered          Y > 0: Up
         */
        int8_t x = 0, y = 0;
    };

    struct Mods {
        bool shift = false;
        bool control = false;
        bool alt = false;
        bool super = false;
        bool capsLock = false;
        bool numLock = false;
    };

    class InputSystem {
    public:

        virtual bool isKeyPressed(const Key& key) = 0;
        virtual bool isKeyJustPressed(const Key& key) = 0;
        virtual bool isKeyJustReleased(const Key& key) = 0;

        virtual bool isMouseButtonPressed(const uint8_t& button) = 0;
        virtual bool isMouseButtonJustPressed(const uint8_t& button) = 0;
        virtual bool isMouseButtonJustReleased(const uint8_t& button) = 0;

        virtual bool isMouseButtonPressed(const Button& button) = 0;
        virtual bool isMouseButtonJustPressed(const Button& button) = 0;
        virtual bool isMouseButtonJustReleased(const Button& button) = 0;

//        virtual bool

    };
}

namespace kat::event::os::input {

}