#include "Window.h"
#include "Input.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <spdlog/spdlog.h>
#include <string>

Window::Window(const std::string& title, int w, int h): m_title(title), m_width(w), m_height(h)
{
};

Window::~Window()
{
    if(m_glContext)
    {
        SDL_GL_DeleteContext(m_glContext);
        m_glContext = nullptr;
    }

    if(m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    SDL_Quit();
}

void Window::swap()
{
    SDL_GL_SwapWindow(m_window);
}

void Window::pollEvents(Input& input)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        input.handleEvent(event);
        switch(event.type)
        {
            case SDL_QUIT:
                m_shouldClose = true;
                break;
        }
    }
}

bool Window::init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        spdlog::error("SDL initialization failed: {}", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(!m_window)
    {
        spdlog::error("SDL window creation failed: {}", SDL_GetError());
        return false;
    }

    m_glContext = SDL_GL_CreateContext(m_window);
    if(!m_glContext)
    {
        spdlog::error("SDL GL context creation failed: {}", SDL_GetError());
        return false;
    }

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        spdlog::error("glewInit failed");
        return false;
    }

    SDL_GL_SetSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    return true;
}
