#ifndef DEF_SHADER
#define DEF_SHADER


// Include Windows

#ifdef WIN32
#include <GL/glew.h>


// Include Mac

#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>


// Include UNIX/Linux

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Includes communs

#include <iostream>
#include <string>
#include <fstream>



class Shader
{
    public:
        Shader();
        Shader(std::string vertexSource, std::string fragmentSource);
        Shader(Shader const &shader);
        Shader& operator=(Shader const &shader);
        bool load();
        bool shaderCompilation(GLuint &shader, GLenum type, std::string const &source);
        GLuint getProgramID() const;
        void sendMat4(glm::mat4 matrice, std::string name);
        ~Shader();
    private:
        GLuint m_vertexID;
        GLuint m_fragmentID;
        GLuint m_programID;
        std::string m_vertexSource;
        std::string m_fragmentSource;
};

#endif
