#ifndef DEF_CAMERA
#define DEF_CAMERA

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif // WIN32

#include "Input.h"

class Camera
{
    public:
        Camera();
        Camera(glm::vec3 position, glm::vec3 pointFixe, glm::vec3 vertical);
        void orienter(int xRel, int yRel);
        void deplacer(Input const& input);
        void lookAt(glm::mat4 &modelview);
        void setPointFixe(glm::vec3 pointFixe);
        void setPosition(glm::vec3 const position);
        float getVitesse() const;
        float getSensibilite() const;
        void setVitesse(float vitesse);
        void setSensibilite(float sensibilite);
        ~Camera();
    private:
        float m_phi;
        float m_theta;
        glm::vec3 m_orientation;
        glm::vec3 m_vertical;
        glm::vec3 m_deplacement;
        glm::vec3 m_position;
        glm::vec3 m_pointFixe;
        float m_vitesse;
        float m_sensibilite;
};

#endif // DEF_CAMERA
