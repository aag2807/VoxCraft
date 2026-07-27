#include "Input.h"
#include <SDL2/SDL_events.h>
#include <cinttypes>
#include <cstring>

void Input::beginFrame()
{
    m_pressed.clear();
    m_released.clear();
    std::memset(m_mousePressed, 0, sizeof(m_mousePressed));
    m_mouseX = 0;
    m_mouseY = 0;
}

void Input::handleEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            if(!m_down[event.key.keysym.scancode])
            {
                m_pressed[event.key.keysym.scancode] = true;
            }
            m_down[event.key.keysym.scancode] = true;
            break;
        case SDL_KEYUP:
            m_released[event.key.keysym.scancode] = true;
            m_down[event.key.keysym.scancode] = false;
            break;
        case SDL_MOUSEMOTION:
            m_mouseX += event.motion.xrel;
            m_mouseY += event.motion.yrel;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            int idx = event.button.button - 1;
            if(idx >= 0 && idx < NUM_MOUSE_BUTTONS)
            {
                bool down = (event.type == SDL_MOUSEBUTTONDOWN);
                if(down && !m_mouseButtons[idx])
                {
                    m_mousePressed[idx] = true;
                }
                m_mouseButtons[idx] = down;
            }
            break;
    }
}

bool Input::keyDown(SDL_Scancode s) const {
    auto it = m_down.find(s);
    return it != m_down.end() && it->second;
}

bool Input::keyPressed(SDL_Scancode s) const {
    auto it = m_pressed.find(s);
    return it != m_pressed.end() && it->second;
}

bool Input::keyReleased(SDL_Scancode s) const {
    auto it = m_released.find(s);
    return it != m_released.end() && it->second;
}

bool Input::mouseDown(int b) const {
    int idx = b - 1;
    return idx >= 0 && idx < NUM_MOUSE_BUTTONS && m_mousePressed[idx];
}

bool Input::mousePressed(int b) const {
    int idx = b - 1;
    return idx >= 0 && idx < NUM_MOUSE_BUTTONS && m_mousePressed[idx];
}

void Input::setMouseLocked(bool locked) {
    m_mouseLocked = locked;
    SDL_SetRelativeMouseMode(locked ? SDL_TRUE : SDL_FALSE);
}
