#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>

class Camera
{
    public:
        Camera();

        void rotate(float dx, float dy, float sensitivity = 0.2f);
        void move(glm::vec3 delta);

        glm::mat4 viewMatrix() const;
        glm::mat4 projectionMatrix( float aspect, float fov = 70.0f, float nearP = 0.1f, float farP = 1000.0f ) const;

        void extractFrustum(float aspect, float pov, float nearP, float farP);
        bool chunkInFrustum(glm::vec3 mn, glm::vec3 mx) const;

        glm::vec3 position() const { return m_pos; }
        glm::vec3 forward() const;
        glm::vec3 right() const;

        void setPosition(glm::vec3 pos) { m_pos = pos; }

        const float* frustumPlanes() const { return &m_frustum[0][0]; }

    private:
        glm::vec3 m_pos;
        float m_yaw = 0;
        float m_pitch = 0;
        float m_frustum[6][4];
        void updatePlate(int idx, glm::vec3 normal, float d);
};
