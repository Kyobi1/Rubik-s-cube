#include "Camera.h"

Camera::Camera() : m_phi(0.0), m_theta(0.0), m_orientation(), m_vertical(0, 0, 1), m_deplacement(), m_position(), m_pointFixe(), m_vitesse(0.5), m_sensibilite(0.5)
{

}

Camera::Camera(glm::vec3 position, glm::vec3 pointFixe, glm::vec3 vertical) : m_phi(0.0), m_theta(0.0), m_orientation(), m_vertical(glm::normalize(vertical)), m_deplacement(), m_position(position), m_pointFixe(pointFixe), m_vitesse(0.5), m_sensibilite(0.5)
{
setPointFixe(pointFixe);
}

void Camera::orienter(int xRel, int yRel)
{
    float thetaRad(0.0), phiRad(0.0);

    m_theta += -xRel*m_sensibilite;
    m_phi += -yRel*m_sensibilite;

    if (m_phi > 89.0)
    {
        m_phi = 89.0;
    }
    else if (m_phi < -89.0)
    {
        m_phi = -89.0;
    }

    thetaRad = m_theta*M_PI/180;
    phiRad = m_phi*M_PI/180;

    if (m_vertical.x == 1.0)
    {
        m_orientation.x = sin(phiRad);
        m_orientation.y = cos(phiRad) * cos(thetaRad);
        m_orientation.z = cos(phiRad) * sin(thetaRad);
    }
    else if (m_vertical.y == 1.0)
    {
        m_orientation.x = cos(phiRad) * sin(thetaRad);
        m_orientation.y = sin(phiRad);
        m_orientation.z = cos(phiRad) * cos(thetaRad);
    }
    else if (m_vertical.z == 1.0)
    {
        m_orientation.x = cos(phiRad) * cos(thetaRad);
        m_orientation.y = cos(phiRad) * sin(thetaRad);
        m_orientation.z = sin(phiRad);
    }

    m_deplacement = glm::cross(m_vertical, m_orientation);
    m_deplacement = glm::normalize(m_deplacement);

    m_pointFixe = m_position + m_orientation;
}

void Camera::deplacer(Input const& input)
{
    if (input.getKeyPressed(SDL_SCANCODE_RIGHT))
    {
        m_position -= m_deplacement * m_vitesse;
        m_pointFixe = m_position + m_orientation;
    }
    if (input.getKeyPressed(SDL_SCANCODE_LEFT))
    {
        m_position += m_deplacement * m_vitesse;
        m_pointFixe = m_position + m_orientation;
    }
    if (input.getKeyPressed(SDL_SCANCODE_UP))
    {
        m_position += m_orientation * m_vitesse;
        m_pointFixe = m_position + m_orientation;
    }
    if (input.getKeyPressed(SDL_SCANCODE_DOWN))
    {
        m_position -= m_orientation * m_vitesse;
        m_pointFixe = m_position + m_orientation;
    }
    if (input.getMouseMoved())
    {
        orienter(input.getMouseRelativeX(), input.getMouseRelativeY());
    }
}

void Camera::lookAt(glm::mat4 &modelview)
{
    modelview = glm::lookAt(m_position, m_pointFixe, m_vertical);
}

void Camera::setPointFixe(glm::vec3 pointFixe)
{
    float thetaRad(0.0), phiRad(0.0);

    m_pointFixe = pointFixe;

    m_orientation = m_pointFixe - m_position;
    m_orientation = glm::normalize(m_orientation);

    if (m_vertical.x == 1.0)
    {
        phiRad = asin(m_orientation.x);
        thetaRad = acos(m_orientation.y/cos(phiRad));
        if (m_orientation.y < 0)
        {
            thetaRad *= -1;
        }
    }
    else if (m_vertical.y == 1.0)
    {
        phiRad = asin(m_orientation.y);
        thetaRad = acos(m_orientation.z/cos(phiRad));
        if (m_orientation.z < 0)
        {
            thetaRad *= -1;
        }
    }
    else if (m_vertical.z == 1.0)
    {
        phiRad = asin(m_orientation.x);
        thetaRad = acos(m_orientation.z/cos(phiRad));
        if (m_orientation.z < 0)
        {
            thetaRad *= -1;
        }
    }

    m_theta = thetaRad * 180 / M_PI;
    m_phi = phiRad * 180 / M_PI;
}

void Camera::setPosition(glm::vec3 position)
{
    m_position = position;
    m_pointFixe = m_position + m_orientation;
}

float Camera::getVitesse() const
{
    return m_vitesse;
}

float Camera::getSensibilite() const
{
    return m_sensibilite;
}

void Camera::setVitesse(float vitesse)
{
    m_vitesse = vitesse;
}

void Camera::setSensibilite(float sensibilite)
{
    m_sensibilite = sensibilite;
}

Camera::~Camera()
{

}
