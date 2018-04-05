#ifndef CUBE_H
#define CUBE_H

#include <SDL2/SDL.h>
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

#include "Shader.h"

class Cube
{
    public:
        Cube();
        Cube(glm::vec3 const center, float const cubeSize, std::string const vertexShader = "Shaders/couleur3D.vert", std::string const fragmentShader = "Shaders/couleur3D.frag");
        Cube(glm::vec3 const center, float const cubeSize, SDL_Color color, std::string const vertexShader = "Shaders/couleur3D.vert", std::string const fragmentShader = "Shaders/couleur3D.frag");
        Cube(glm::vec3 const center, float const cubeSize, SDL_Color color1, SDL_Color color2, SDL_Color color3 = {255, 255, 255}, SDL_Color color4 = {255, 255, 255}, SDL_Color color5 = {255, 255, 255}, SDL_Color color6 = {255, 255, 255}, std::string const vertexShader = "Shaders/couleur3D.vert", std::string const fragmentShader = "Shaders/couleur3D.frag");
        Cube(Cube const &cubeCopy);
        Cube& operator=(Cube const &cubeCopy);
        void load();
        void updateVBO(void *donnees, int tailleBytes, int decalage);
        void draw(glm::mat4 modelview, glm::mat4 projection);
        void setColorFace(int face, SDL_Color color);
        void turn(glm::vec3 centerRotation, float angle, glm::vec3 axe);
        float getVertice(int index) const;
        glm::vec3 getCenter() const;
        ~Cube();
    protected:
        Shader m_shader;
        float m_vertices[108];
        float m_colors[108];
        GLuint m_vboID;
        GLuint m_vaoID;
        int m_verticesSize;
        int m_colorsSize;
        glm::vec3 m_center;
    private:

};

#endif // CUBE_H
