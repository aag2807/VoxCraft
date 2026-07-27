#pragma once
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <unordered_map>
#include <SDL2/SDL.h>

class Input
{
    public:
        void beginFrame();
        void handleEvent(const SDL_Event& event);

        bool keyDown(SDL_Scancode s) const;
        bool keyPressed(SDL_Scancode s) const;
        bool keyReleased(SDL_Scancode s) const;

        int mouseDX() const { return m_mouseX; }
        int mouseDY() const { return m_mouseY; }

        bool mouseDown(int sdlButton) const;
        bool mousePressed(int sdlButton) const;

        void setMouseLocked(bool locked);
        bool mouseLocked() const { return m_mouseLocked; }

    private:
        static constexpr int NUM_MOUSE_BUTTONS = 5; // l, m, r, x1, x2

        std::unordered_map<SDL_Scancode, bool> m_down;
        std::unordered_map<SDL_Scancode, bool> m_pressed;
        std::unordered_map<SDL_Scancode, bool> m_released;

        int m_mouseX = 0;
        int m_mouseY = 0;

        bool m_mouseButtons[NUM_MOUSE_BUTTONS] = {};
        bool m_mousePressed[NUM_MOUSE_BUTTONS] = {};
        bool m_mouseLocked = false;
};
