#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : m_pos(0, 100, 0)
{
}

void Camera::rotate(float dx, float dy, float sens)
{
    m_yaw += dx * sens;
    m_pitch = glm::clamp(m_pitch - dy * sens, -89.0f, 89.0f);
}

void Camera::move(glm::vec3 delta)
{
    m_pos += delta;
}

glm::vec3 Camera::forward() const
{
    float cy = glm::cos(glm::radians(m_yaw));
    float sy = glm::sin(glm::radians(m_yaw));
    float cp = glm::cos(glm::radians(m_pitch));
    float sp = glm::sin(glm::radians(m_pitch));

    return glm::normalize(glm::vec3(sy*cp, sp, cy * cp));
}

glm::vec3 Camera::right() const
{
    return glm::normalize(glm::cross(forward(), glm::vec3(0, 1, 0)));
}

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(m_pos, m_pos + forward(), glm::vec3(0, 1, 0));
}

glm::mat4 Camera::projectionMatrix(float aspect, float fov, float nearP, float farP) const
{
    return glm::perspective(glm::radians(fov), aspect, nearP, farP);
}

void Camera::extractFrustum(float aspect, float fov, float nearP, float farP)
{
    glm::mat4 proj = projectionMatrix(aspect, fov, nearP, farP);

    auto row = [&](int r) {
        return glm::vec4(proj[0][r], proj[1][r], proj[2][r], proj[3][r]);
    };

    glm::vec4 planes[6] = {
        row(3) + row(0), // left
        row(3) - row(0), // right
        row(3) + row(1), // bottom
        row(3) - row(1), // top
        row(3) + row(2), // near
        row(3) - row(2), // far
    };

    for(int i = 0; i < 6; i++)
    {
        glm::vec4 pl = planes[i];
        float len = glm::length(glm::vec3(pl));
        pl /= len; //normalize planes
        m_frustum[i][0] = pl.x;
        m_frustum[i][1] = pl.y;
        m_frustum[i][2] = pl.z;
        m_frustum[i][3] = pl.w;
    }
}

bool Camera::chunkInFrustum(glm::vec3 mn, glm::vec3 mx) const
{
    for(int i = 0; i < 6; i++)
    {
        glm::vec3 n(m_frustum[i][0], m_frustum[i][1], m_frustum[i][2]);
        glm::vec3 pv(
            n.x >= 0 ? mx.x : mn.x,
            n.y >= 0 ? mx.y : mn.y,
            n.z >= 0 ? mx.z : mn.z
        );

       if(glm::dot(n, pv) + m_frustum[i][3] < 0)
       {
           return false;
       }
    }

    return true;
}
