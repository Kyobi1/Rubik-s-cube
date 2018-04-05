#include <cstring>
#include "Cube.h"
#include "maths.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

#define DEFAULT_SIZE 1

Cube::Cube() : m_vertices({-DEFAULT_SIZE, 0, -DEFAULT_SIZE,  -DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,  DEFAULT_SIZE, 0, -DEFAULT_SIZE,  -DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,  DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,  DEFAULT_SIZE, 0, -DEFAULT_SIZE,
                -DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,  -DEFAULT_SIZE, 0, -DEFAULT_SIZE,  -DEFAULT_SIZE, 0, DEFAULT_SIZE,  -DEFAULT_SIZE, 0, DEFAULT_SIZE,  -DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE,  -DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,
                -DEFAULT_SIZE, 0, -DEFAULT_SIZE,  DEFAULT_SIZE, 0, -DEFAULT_SIZE,  DEFAULT_SIZE, 0, DEFAULT_SIZE,  DEFAULT_SIZE, 0, DEFAULT_SIZE,  -DEFAULT_SIZE, 0, DEFAULT_SIZE,  -DEFAULT_SIZE, 0, -DEFAULT_SIZE,
                DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,  DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE,  DEFAULT_SIZE, 0, -DEFAULT_SIZE,  DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE,  DEFAULT_SIZE, 0, DEFAULT_SIZE,  DEFAULT_SIZE, 0, -DEFAULT_SIZE,
                -DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,  DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,  DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE,  DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE,  -DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE,  -DEFAULT_SIZE, 2*DEFAULT_SIZE, -DEFAULT_SIZE,
                -DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE,  DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE,  DEFAULT_SIZE, 0, DEFAULT_SIZE,  DEFAULT_SIZE, 0, DEFAULT_SIZE,  -DEFAULT_SIZE, 0, DEFAULT_SIZE,  -DEFAULT_SIZE, 2*DEFAULT_SIZE, DEFAULT_SIZE}),

                m_colors ({1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,
                0, 1, 0,  0, 1, 0,  0, 1, 0,  0, 1, 0,  0, 1, 0,  0, 1, 0,
                0, 0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1,
                1, 1, 0,  1, 1, 0,  1, 1, 0,  1, 1, 0,  1, 1, 0,  1, 1, 0,
                0, 1, 1,  0, 1, 1,  0, 1, 1,  0, 1, 1,  0, 1, 1,  0, 1, 1,
                1, 0, 1,  1, 0, 1,  1, 0, 1,  1, 0, 1,  1, 0, 1,  1, 0, 1
                }),

                m_shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag"),
                m_vboID(0), m_vaoID(0), m_verticesSize(108 * sizeof(float)), m_colorsSize(108 * sizeof(float)), m_center(glm::vec3 (0, DEFAULT_SIZE, 0))
{
    m_shader.load();
}

Cube::Cube(glm::vec3 const center, float const cubeSize, std::string const vertexShader, std::string const fragmentShader) : m_vertices ({center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2}),

                m_shader(vertexShader, fragmentShader),
                m_vboID(0), m_vaoID(0), m_verticesSize(108 * sizeof(float)), m_colorsSize(108 * sizeof(float)), m_center(center)
{
    m_shader.load();
}

Cube::Cube(glm::vec3 const center, float const cubeSize, SDL_Color color, std::string const vertexShader, std::string const fragmentShader) : m_vertices ({center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2}),

                m_shader(vertexShader, fragmentShader),
                m_vboID(0), m_vaoID(0), m_verticesSize(108 * sizeof(float)), m_colorsSize(108 * sizeof(float)), m_center(center)
{
    for(int i = 0; i < 6; i ++)
    {
        setColorFace(i, color);
    }
    m_shader.load();
}

Cube::Cube(glm::vec3 const center, float const cubeSize, SDL_Color color1, SDL_Color color2, SDL_Color color3, SDL_Color color4, SDL_Color color5, SDL_Color color6, std::string const vertexShader, std::string const fragmentShader) :
                m_vertices ({center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z - cubeSize/2,
                center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2,  center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,
                center.x + cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y - cubeSize/2, center.z + cubeSize/2,  center.x - cubeSize/2, center.y + cubeSize/2, center.z + cubeSize/2}),

                m_shader(vertexShader, fragmentShader),
                m_vboID(0), m_vaoID(0), m_verticesSize(108 * sizeof(float)), m_colorsSize(108 * sizeof(float)), m_center(center)
{
    for(int i = 0; i < 6; i ++)
    {
        switch(i)
        {
            case 0:
                setColorFace(i, color1);
            break;
            case 1:
                setColorFace(i, color2);
            break;
            case 2:
                setColorFace(i, color3);
            break;
            case 3:
                setColorFace(i, color4);
            break;
            case 4:
                setColorFace(i, color5);
            break;
            case 5:
                setColorFace(i, color6);
            break;
            default:
            break;
        }
    }
    m_shader.load();
}

Cube::Cube(Cube const &cubeCopy) : m_shader(cubeCopy.m_shader), m_vboID(0), m_vaoID(0), m_verticesSize(cubeCopy.m_verticesSize), m_colorsSize(cubeCopy.m_colorsSize), m_center(cubeCopy.m_center)
{
    for (int i = 0; i < 108; i ++)
    {
        m_vertices[i] = cubeCopy.m_vertices[i];
        m_colors[i] = cubeCopy.m_colors[i];
    }
    m_shader.load();
}

Cube& Cube::operator=(Cube const &cubeCopy)
{
    for (int i = 0; i < 108; i ++)
    {
        m_vertices[i] = cubeCopy.m_vertices[i];
        m_colors[i] = cubeCopy.m_colors[i];
    }
    m_shader = cubeCopy.m_shader;
    m_vboID = 0;
    m_vaoID = 0;
    m_verticesSize = cubeCopy.m_verticesSize;
    m_colorsSize = cubeCopy.m_colorsSize;
    m_center = cubeCopy.m_center;
    m_shader.load();
    return *this;
}

void Cube::load()
{
    if (glIsBuffer(m_vboID))
    {
        glDeleteBuffers(1, &m_vboID);
    }
    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        glBufferData(GL_ARRAY_BUFFER, m_verticesSize + m_colorsSize, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticesSize, m_vertices);
        glBufferSubData(GL_ARRAY_BUFFER, m_verticesSize, m_colorsSize, m_colors);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (glIsVertexArray(m_vaoID) == GL_TRUE)
    {
        glDeleteVertexArrays(1, &m_vaoID);
    }
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesSize));
            glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Cube::updateVBO(void *donnees, int tailleBytes, int decalage)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        void* adresse = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

        if (adresse == NULL)
        {
            std::cout << "Erreur au niveau de la récupération du VBO" << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            return;
        }

        memcpy((char*)adresse + decalage, donnees, tailleBytes);

        glUnmapBuffer(GL_ARRAY_BUFFER);
        adresse = 0;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::draw(glm::mat4 modelview, glm::mat4 projection)
{
    glUseProgram(m_shader.getProgramID());

        glBindVertexArray(m_vaoID);

            m_shader.sendMat4(projection*modelview, "modelviewProjection");
            glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

    glUseProgram(0);
}

void Cube::setColorFace(int face, SDL_Color color)
{
    for (int j = face*18; j < (face+1)*18; j +=3)
    {
        m_colors[j] = (float)color.r/255;
        m_colors[j + 1] = (float)color.g/255;
        m_colors[j + 2] = (float)color.b/255;
    }
}

void Cube::turn(glm::vec3 centerRotation, float angle, glm::vec3 axe)
{
    float x, y, z;
    glm::vec3 turned;
    // Rotation de chaque arête du cube
    for (int i = 0; i < 107; i += 3)
    {
        x = m_vertices[i] - centerRotation.x;
        y = m_vertices[i+1] - centerRotation.y;
        z = m_vertices[i+2] - centerRotation.z;
        turned = rotation(angle, axe, glm::vec3({x, y, z}));
        m_vertices[i] = turned.x + centerRotation.x;
        m_vertices[i+1] = turned.y + centerRotation.y;
        m_vertices[i+2] = turned.z + centerRotation.z;
    }
    // Rotation du centre du cube
    x = m_center.x - centerRotation.x;
    y = m_center.y - centerRotation.y;
    z = m_center.z - centerRotation.z;
    turned = rotation(angle, axe, glm::vec3({x, y, z}));
    m_center.x = turned.x + centerRotation.x;
    m_center.y = turned.y + centerRotation.y;
    m_center.z = turned.z + centerRotation.z;
    updateVBO(m_vertices, m_verticesSize, 0);
}

float Cube::getVertice(int index) const
{
    return m_vertices[index];
}

glm::vec3 Cube::getCenter() const
{
    return m_center;
}

Cube::~Cube()
{
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
}
