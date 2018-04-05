#ifndef SCENEOPENGL_H
#define SCENEOPENGL_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

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

class SceneOpenGl
{
    public:
        SceneOpenGl(std::string name, unsigned int width, unsigned int height);
        bool initWindow();
        bool initGL();
        void mainLoop();
        virtual ~SceneOpenGl();
    protected:
    private:
        SDL_Window *m_window;
        SDL_GLContext m_context;
        Input m_input;
        std::string m_name;
        unsigned int m_width;
        unsigned int m_height;
};

#endif // SCENEOPENGL_H
