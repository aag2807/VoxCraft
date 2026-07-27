#pragma once
#include "Camera.h"
#include "Input.h"
#include "Window.h"

class Engine
{
    public:
        Engine(Window&  window);
        void run();
    private:
        Window& m_window;
        Input m_input;
        Camera m_camera;
        double m_lastTime = 0;
        double m_fpsTimer = 0;
        int m_fps = 0;
        int m_frameCount = 0;

        void update(float dt);
        void render(float dt);
};
