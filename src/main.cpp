#include <SDL2/SDL.h>
#include <iostream>
#include "SceneOpenGl.h"

#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif // WIN32


int main(int argc, char **argv)
{
    SceneOpenGl scene1("scene 1", 800, 600);

    scene1.mainLoop();

    return 0;
}
