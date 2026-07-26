#include "Engine.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

Engine::Engine(Window& window) : m_window(window)
{
}

void Engine::run()
{
    m_lastTime = SDL_GetTicks64() / 1000.0;
    while(!m_window.shouldClose())
    {
        double now = SDL_GetTicks64() / 1000.0;
        float dt = float(now - m_lastTime);
        m_lastTime = now;

        m_window.pollEvents();
        update(dt);
        render(dt);
        m_window.swap();

        //fps counter
        m_frameCount++;
        m_fpsTimer += dt;
        if(m_fpsTimer >= 1.0)
        {
            m_fps = m_frameCount;
            m_frameCount = 0;
            m_fpsTimer -= 1.0;
        }
    }

}

void Engine::update(float dt)
{
}

void Engine::render(float dt)
{
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
