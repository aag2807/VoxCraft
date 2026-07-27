#include "Engine.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <glm/geometric.hpp>

Engine::Engine(Window& window) : m_window(window)
{
    m_camera = Camera();
    m_input = Input();
}

void Engine::run()
{
    m_lastTime = SDL_GetTicks64() / 1000.0;
    while(!m_window.shouldClose())
    {
        double now = SDL_GetTicks64() / 1000.0;
        float dt = float(now - m_lastTime);
        m_lastTime = now;

        m_input.beginFrame();
        m_window.pollEvents(m_input);
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
    if(m_input.mouseLocked())
    {
        m_camera.rotate(m_input.mouseDX(), m_input.mouseDY());
    }

    glm::vec3 move(0);

    if (m_input.keyDown(SDL_SCANCODE_W))
    {
        move += m_camera.forward();
    }

    if (m_input.keyDown(SDL_SCANCODE_S))
    {
        move -= m_camera.forward();
    }
    if (m_input.keyDown(SDL_SCANCODE_A))
    {
        move -= m_camera.right();
    }
    if (m_input.keyDown(SDL_SCANCODE_D))
    {
        move += m_camera.right();
    }
    if (m_input.keyDown(SDL_SCANCODE_SPACE))
    {
        move.y += 1;
    }
    if (m_input.keyDown(SDL_SCANCODE_LSHIFT))
    {
        move.y -= 1;
    }

    float speed = 50.0f;
    if(glm::length(move) > 0)
    {
        m_camera.move(glm::normalize(move) * speed * dt);
    }

    if(m_input.keyPressed(SDL_SCANCODE_TAB))
    {
        m_input.setMouseLocked(!m_input.mouseLocked());
    }

}

void Engine::render(float dt)
{
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
