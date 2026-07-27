#pragma once

#include "Input.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_video.h>
#include <string>

class Window
{
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    bool init();
    void swap();
    void pollEvents(Input& input);

    SDL_Window* getSDLWindow() const { return m_window; }
    SDL_GLContext getGLContext() const { return m_glContext; }
    int width() const { return m_width; }
    int height() const { return m_height; }
    bool shouldClose() const { return m_shouldClose; }
    void requestClose() { m_shouldClose = true; }

private:
    std::string m_title;
    int m_width;
    int m_height;
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;
    bool m_shouldClose = false;
};
