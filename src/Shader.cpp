#include "Shader.h"

Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(""), m_fragmentSource("")
{

}

Shader::Shader(std::string vertexSource, std::string fragmentSource) : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{

}

Shader::Shader(Shader const &shader) : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(shader.m_vertexSource), m_fragmentSource(shader.m_fragmentSource)
{
    load();
}

Shader& Shader::operator=(Shader const &shader)
{
    m_vertexSource = shader.m_vertexSource;
    m_fragmentSource = shader.m_fragmentSource;
    load();
    return *this;
}

bool Shader::load()
{
    if (glIsShader(m_vertexID) == GL_TRUE)
    {
        glDeleteShader(m_vertexID);
    }
    if (glIsShader(m_fragmentID) == GL_TRUE)
    {
        glDeleteShader(m_fragmentID);
    }
    if (glIsProgram(m_programID) == GL_TRUE)
    {
        glDeleteProgram(m_programID);
    }

    if (!shaderCompilation(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
    {
        return false;
    }
    if (!shaderCompilation(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
    {
        return false;
    }

    m_programID = glCreateProgram();

    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    glBindAttribLocation(m_programID, 0, "in_vertex");
    glBindAttribLocation(m_programID, 1, "in_color");
    glBindAttribLocation(m_programID, 2, "in_texCoord0");

    glLinkProgram(m_programID);

    GLint error(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &error);
    if (error != GL_TRUE)
    {
        GLint errorSize(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &errorSize);
        char *errorLog = new char [errorSize + 1];
        glGetProgramInfoLog(m_programID, errorSize, &errorSize, errorLog);
        errorLog[errorSize] = '\0';
        std::cout << "Erreur lors du linkage du programme : " << errorLog << std::endl;
        delete[] errorLog;
        glDeleteProgram(m_programID);
        return false;
    }
}

bool Shader::shaderCompilation(GLuint &shader, GLenum type, std::string const &source)
{
    shader = glCreateShader(type);
    if (shader == 0)
    {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }

    std::ifstream file(source.c_str());
    if (file == NULL)
    {
        std::cout << "Erreur, le fichier " << source << "est introuvable" << std::endl;
        glDeleteShader(shader);
        return false;
    }

    std::string ligne;
    std::string code;

    while(std::getline(file, ligne))
    {
        code += ligne + '\n';
    }

    file.close();

    const GLchar *code2 = code.c_str();

    glShaderSource(shader, 1, &code2, 0);

    glCompileShader(shader);

    GLint error(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
    if (error != GL_TRUE)
    {
        GLint errorSize(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);
        char *errorLog = new char [errorSize + 1];
        glGetShaderInfoLog(shader, errorSize, &errorSize, errorLog);
        errorLog[errorSize] = '\0';
        std::cout << "Erreur lors de la compilation du shader : " << errorLog << std::endl;
        delete[] errorLog;
        glDeleteShader(shader);
        return false;
    }
    else
    {
        return true;
    }
}

GLuint Shader::getProgramID() const
{
    return m_programID;
}

void Shader::sendMat4(glm::mat4 matrice, std::string name)
{
    glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrice));
}

Shader::~Shader()
{
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}
