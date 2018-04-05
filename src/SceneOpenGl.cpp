#include "SceneOpenGl.h"
#include "Cube.h"
#include "Camera.h"
#include "Shader.h"
#include "RubiksCube.h"
#define FRAMERATE 60

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif


SceneOpenGl::SceneOpenGl(std::string name, unsigned int width, unsigned int height) : m_name(name), m_width(width), m_height(height), m_input()
{
    initWindow();
    initGL();
}

SceneOpenGl::~SceneOpenGl()
{
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool SceneOpenGl::initWindow()
{
    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Création de la fenêtre

    m_window = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_window == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    m_context = SDL_GL_CreateContext(m_window);

    if(m_context == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }
    return true;
}

bool SceneOpenGl::initGL()
{
    #ifdef WIN32

    GLenum initGlew(glewInit());
    if(initGlew != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initGlew) << std::endl;


            // On quitte la SDL

            SDL_GL_DeleteContext(m_context);
            SDL_DestroyWindow(m_window);
            SDL_Quit();

            return false;
        }
    #endif // WIN32

    glEnable(GL_DEPTH_TEST);

    return true;
}

void SceneOpenGl::mainLoop()
{
    const float framerate = 1000/FRAMERATE;

    Uint32 tempsDepart(0), tempsFin(0), tempsEcoule(0);

    bool stop(false);

    bool pressed(false);
    bool pressed2(false);
    bool pressed3(false);
    bool pressed4(false);
    bool pressed5(false);
    bool pressed6(false);
    bool pressed7(false);

    bool sense(true);

    SDL_Color red;
    red.r = 255;
    red.g = 0;
    red.b = 0;

    SDL_Color green;
    green.r = 0;
    green.g = 255;
    green.b = 0;

    SDL_Color blue;
    blue.r = 0;
    blue.g = 0;
    blue.b = 255;

    SDL_Color yellow;
    yellow.r = 0;
    yellow.g = 255;
    yellow.b = 255;

    SDL_Color purple;
    purple.r = 255;
    purple.g = 0;
    purple.b = 255;

    SDL_Color white;
    white.r = 255;
    white.g = 255;
    white.b = 255;

    glm::mat4 modelview;
    glm::mat4 projection;

    modelview = glm::mat4(1.0);
    projection = glm::perspective(70.0, (double) m_width/m_height, 0.1, 100.0);

    Camera camera(glm::vec3(12.0, 12.0, 12.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    RubiksCube rubiksCube;

    m_input.setRelativeMode(true);

    while (!m_input.getStop() && !stop)
    {
        tempsDepart = SDL_GetTicks();

        if (m_input.getKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            stop = true;
        }

        if (m_input.getKeyPressed(SDL_SCANCODE_S) && !pressed7)
        {
            sense = !sense;
            pressed7 = true;
        }
        else if (!m_input.getKeyPressed(SDL_SCANCODE_S))
        {
            pressed7 = false;
        }

        if (m_input.getKeyPressed(SDL_SCANCODE_F) && !pressed && (rubiksCube.getRotEnCours() == 6 || rubiksCube.getRotEnCours() == 0))
        {
            rubiksCube.turnFace(0, sense);
            pressed = true;
        }
        else if (!m_input.getKeyPressed(SDL_SCANCODE_F))
        {
            pressed = false;
        }

        if (m_input.getKeyPressed(SDL_SCANCODE_X) && !pressed2 && (rubiksCube.getRotEnCours() == 6 || rubiksCube.getRotEnCours() == 1))
        {
            rubiksCube.turnFace(1, sense);
            pressed2 = true;
        }
        else if (!m_input.getKeyPressed(SDL_SCANCODE_X))
        {
            pressed2 = false;
        }

        if (m_input.getKeyPressed(SDL_SCANCODE_V) && !pressed3 && (rubiksCube.getRotEnCours() == 6 || rubiksCube.getRotEnCours() == 2))
        {
            rubiksCube.turnFace(2, sense);
            pressed3 = true;
        }
        else if (!m_input.getKeyPressed(SDL_SCANCODE_V))
        {
            pressed3 = false;
        }

        if (m_input.getKeyPressed(SDL_SCANCODE_B) && !pressed4 && (rubiksCube.getRotEnCours() == 6 || rubiksCube.getRotEnCours() == 3))
        {
            rubiksCube.turnFace(3, sense);
            pressed4 = true;
        }
        else if (!m_input.getKeyPressed(SDL_SCANCODE_B))
        {
            pressed4 = false;
        }

        if (m_input.getKeyPressed(SDL_SCANCODE_C) && !pressed5 && (rubiksCube.getRotEnCours() == 6 || rubiksCube.getRotEnCours() == 4))
        {
            rubiksCube.turnFace(4, sense);
            pressed5 = true;
        }
        else if (!m_input.getKeyPressed(SDL_SCANCODE_C))
        {
            pressed5 = false;
        }

        if (m_input.getKeyPressed(SDL_SCANCODE_SPACE) && !pressed6 && (rubiksCube.getRotEnCours() == 6 || rubiksCube.getRotEnCours() == 5))
        {
            rubiksCube.turnFace(5, sense);
            pressed6 = true;
        }
        else if (!m_input.getKeyPressed(SDL_SCANCODE_SPACE))
        {
            pressed6 = false;
        }

        if (m_input.getKeyPressed(SDL_SCANCODE_RIGHT))
        {
            rubiksCube.turnCube(1, true);
        }
        else if (m_input.getKeyPressed(SDL_SCANCODE_LEFT))
        {
            rubiksCube.turnCube(1, false);
        }
        if (m_input.getKeyPressed(SDL_SCANCODE_UP))
        {
            camera.setPosition(glm::vec3(12, 12, 12));
            camera.setPointFixe(glm::vec3(0, 0, 0));
        }
        if (m_input.getKeyPressed(SDL_SCANCODE_DOWN))
        {
            camera.setPosition(glm::vec3(12, -6, 12));
            camera.setPointFixe(glm::vec3(0, 2, 0));
        }

        m_input.update();

        //camera.deplacer(m_input);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rubiksCube.draw(modelview, projection);

        camera.lookAt(modelview);

        SDL_GL_SwapWindow(m_window);

        tempsFin = SDL_GetTicks();
        tempsEcoule = tempsFin - tempsDepart;
        if (tempsEcoule < framerate)
        {
            SDL_Delay(framerate - tempsEcoule);
        }
    }
}
