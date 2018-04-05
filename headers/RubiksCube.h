#ifndef DEF_RUBIKS_CUBE
#define DEF_RUBIKS_CUBE

#include "Cube.h"

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

class RubiksCube
{
    public:
        RubiksCube();
        void draw(glm::mat4 modelview, glm::mat4 projection);
        void turnFace(int face, bool sense);
        void turnCube(float angle, bool sense);
        bool state();
        int getRotEnCours() const;
        bool appartientFace(int face, Cube const &cube);
        ~RubiksCube();
    private:
        Cube m_cubes[3][3][3];
        int m_rotEnCours;
};

#endif // DEF_RUBIKS_CUBE
