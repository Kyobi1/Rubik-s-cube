#include "RubiksCube.h"
#include "maths.h"

RubiksCube::RubiksCube() : m_rotEnCours(6)
{
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
    yellow.r = 255;
    yellow.g = 255;
    yellow.b = 0;

    SDL_Color orange;
    orange.r = 255;
    orange.g = 102;
    orange.b = 0;

    SDL_Color white;
    white.r = 255;
    white.g = 255;
    white.b = 255;

    SDL_Color black;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    float cubeSize(1.9);

    m_cubes[0][0][0] = Cube(glm::vec3(0, 0, 0), cubeSize, green, orange, white, black, black, black);
    m_cubes[0][0][1] = Cube(glm::vec3(0, 0, 2), cubeSize, black, orange, white, black, black, black);
    m_cubes[0][0][2] = Cube(glm::vec3(0, 0, 4), cubeSize, black, orange, white, black, black, blue);
    m_cubes[0][1][0] = Cube(glm::vec3(0, 2, 0), cubeSize, green, orange, black, black, black, black);
    m_cubes[0][1][1] = Cube(glm::vec3(0, 2, 2), cubeSize, black, orange, black, black, black, black);
    m_cubes[0][1][2] = Cube(glm::vec3(0, 2, 4), cubeSize, black, orange, black, black, black, blue);
    m_cubes[0][2][0] = Cube(glm::vec3(0, 4, 0), cubeSize, green, orange, black, black, yellow, black);
    m_cubes[0][2][1] = Cube(glm::vec3(0, 4, 2), cubeSize, black, orange, black, black, yellow, black);
    m_cubes[0][2][2] = Cube(glm::vec3(0, 4, 4), cubeSize, black, orange, black, black, yellow, blue);
    m_cubes[1][0][0] = Cube(glm::vec3(2, 0, 0), cubeSize, green, black, white, black, black, black);
    m_cubes[1][0][1] = Cube(glm::vec3(2, 0, 2), cubeSize, black, black, white, black, black, black);
    m_cubes[1][0][2] = Cube(glm::vec3(2, 0, 4), cubeSize, black, black, white, black, black, blue);
    m_cubes[1][1][0] = Cube(glm::vec3(2, 2, 0), cubeSize, green, black, black, black, black, black);
    m_cubes[1][1][1] = Cube(glm::vec3(2, 2, 2), cubeSize, black, black, black, black, black, black);
    m_cubes[1][1][2] = Cube(glm::vec3(2, 2, 4), cubeSize, black, black, black, black, black, blue);
    m_cubes[1][2][0] = Cube(glm::vec3(2, 4, 0), cubeSize, green, black, black, black, yellow, black);
    m_cubes[1][2][1] = Cube(glm::vec3(2, 4, 2), cubeSize, black, black, black, black, yellow, black);
    m_cubes[1][2][2] = Cube(glm::vec3(2, 4, 4), cubeSize, black, black, black, black, yellow, blue);
    m_cubes[2][0][0] = Cube(glm::vec3(4, 0, 0), cubeSize, green, black, white, red, black, black);
    m_cubes[2][0][1] = Cube(glm::vec3(4, 0, 2), cubeSize, black, black, white, red, black, black);
    m_cubes[2][0][2] = Cube(glm::vec3(4, 0, 4), cubeSize, black, black, white, red, black, blue);
    m_cubes[2][1][0] = Cube(glm::vec3(4, 2, 0), cubeSize, green, black, black, red, black, black);
    m_cubes[2][1][1] = Cube(glm::vec3(4, 2, 2), cubeSize, black, black, black, red, black, black);
    m_cubes[2][1][2] = Cube(glm::vec3(4, 2, 4), cubeSize, black, black, black, red, black, blue);
    m_cubes[2][2][0] = Cube(glm::vec3(4, 4, 0), cubeSize, green, black, black, red, yellow, black);
    m_cubes[2][2][1] = Cube(glm::vec3(4, 4, 2), cubeSize, black, black, black, red, yellow, black);
    m_cubes[2][2][2] = Cube(glm::vec3(4, 4, 4), cubeSize, black, black, black, red, yellow, blue);

    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 3; j ++)
        {
            for (int k = 0; k < 3; k ++)
            {
                m_cubes[i][j][k].load();
            }
        }
    }
}

void RubiksCube::draw(glm::mat4 modelview, glm::mat4 projection)
{
    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 3; j ++)
        {
            for (int k = 0; k < 3; k ++)
            {
                m_cubes[i][j][k].draw(modelview, projection);
            }
        }
    }
}

void RubiksCube::turnFace(int face, bool sense)
{
    m_rotEnCours = face;
    glm::vec3 cubeCenter = m_cubes[1][1][1].getCenter();
    glm::vec3 vecRotation;
    float angle = 45;
    if (!sense)
        angle *= -1;
    switch (face)
    {
        case 0:
            vecRotation = m_cubes[1][1][0].getCenter() - cubeCenter;
            for (int i = 0; i < 3; i ++)
            {
                for (int j = 0; j < 3; j ++)
                {
                    for (int k = 0; k < 3; k ++)
                    {
                        if (appartientFace(0, m_cubes[i][j][k]))
                            m_cubes[i][j][k].turn(m_cubes[1][1][0].getCenter(), angle, glm::normalize(vecRotation));
                    }
                }
            }
        break;
        case 1:
            vecRotation = m_cubes[0][1][1].getCenter() - cubeCenter;
            for (int i = 0; i < 3; i ++)
            {
                for (int j = 0; j < 3; j ++)
                {
                    for (int k = 0; k < 3; k ++)
                    {
                        if (appartientFace(1, m_cubes[i][j][k]))
                            m_cubes[i][j][k].turn(m_cubes[0][1][1].getCenter(), angle, glm::normalize(vecRotation));
                    }
                }
            }
        break;
        case 2:
            vecRotation = m_cubes[1][0][1].getCenter() - cubeCenter;
            for (int i = 0; i < 3; i ++)
            {
                for (int j = 0; j < 3; j ++)
                {
                    for (int k = 0; k < 3; k ++)
                    {
                        if (appartientFace(2, m_cubes[i][j][k]))
                            m_cubes[i][j][k].turn(m_cubes[1][0][1].getCenter(), angle, glm::normalize(vecRotation));
                    }
                }
            }
        break;
        case 3:
            vecRotation = m_cubes[2][1][1].getCenter() - cubeCenter;
            for (int i = 0; i < 3; i ++)
            {
                for (int j = 0; j < 3; j ++)
                {
                    for (int k = 0; k < 3; k ++)
                    {
                        if (appartientFace(3, m_cubes[i][j][k]))
                            m_cubes[i][j][k].turn(m_cubes[2][1][1].getCenter(), angle, glm::normalize(vecRotation));
                    }
                }
            }
        break;
        case 4:
            vecRotation = m_cubes[1][2][1].getCenter() - cubeCenter;
            for (int i = 0; i < 3; i ++)
            {
                for (int j = 0; j < 3; j ++)
                {
                    for (int k = 0; k < 3; k ++)
                    {
                        if (appartientFace(4, m_cubes[i][j][k]))
                            m_cubes[i][j][k].turn(m_cubes[1][2][1].getCenter(), angle, glm::normalize(vecRotation));
                    }
                }
            }
        break;
        case 5:
            vecRotation = m_cubes[1][1][2].getCenter() - cubeCenter;
            for (int i = 0; i < 3; i ++)
            {
                for (int j = 0; j < 3; j ++)
                {
                    for (int k = 0; k < 3; k ++)
                    {
                        if (appartientFace(5, m_cubes[i][j][k]))
                            m_cubes[i][j][k].turn(m_cubes[1][1][2].getCenter(), angle, glm::normalize(vecRotation));
                    }
                }
            }
        break;
        default:
        break;
    }
    if (state())
    {
        m_rotEnCours = 6;
    }
}

void RubiksCube::turnCube(float angle, bool sense)
{
    if (!sense)
    {
        angle *= -1;
    }
    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 3; j ++)
        {
            for (int k = 0; k < 3; k ++)
            {
                m_cubes[i][j][k].turn(glm::vec3(2, 2, 2), angle, glm::vec3(0, 1, 0));
            }
        }
    }
}

bool RubiksCube::state()
{
    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 3; j ++)
        {
            for (int k = 0; k < 3; k ++)
            {
                int compt = 0;
                if (m_cubes[i][j][k].getCenter() != m_cubes[1][1][0].getCenter() && m_cubes[i][j][k].getCenter() != m_cubes[0][1][1].getCenter() && m_cubes[i][j][k].getCenter() != m_cubes[1][0][1].getCenter() && m_cubes[i][j][k].getCenter() != m_cubes[2][1][1].getCenter() && m_cubes[i][j][k].getCenter() != m_cubes[1][2][1].getCenter() && m_cubes[i][j][k].getCenter() != m_cubes[1][1][2].getCenter())
                {
                    for (int l = 0; l < 6; l ++)
                    {
                        if (appartientFace(l, m_cubes[i][j][k]))
                        {
                            compt ++;
                        }
                        if (compt == 2)
                        {
                            l = 6;
                        }
                    }
                }
                if (compt == 1)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

int RubiksCube::getRotEnCours() const
{
    return m_rotEnCours;
}

bool RubiksCube::appartientFace(int face, Cube const &cube)
{
    glm::vec3 center = cube.getCenter();
    glm::vec3 cubeCenter = m_cubes[1][1][1].getCenter();
    glm::vec3 axis1;

    switch (face)
    {
        case 0:
            axis1 = m_cubes[1][1][0].getCenter() - cubeCenter;
            if (glm::dot((center - m_cubes[1][1][0].getCenter()), axis1) <= 0.1 && glm::dot((center - m_cubes[1][1][0].getCenter()), axis1) >= -0.1)
            {
                return true;
            }
            else
            {
                return false;
            }
        break;
        case 1:
            axis1 = m_cubes[0][1][1].getCenter() - cubeCenter;
            if (glm::dot((center - m_cubes[0][1][1].getCenter()), axis1) <= 0.1 && glm::dot((center - m_cubes[0][1][1].getCenter()), axis1) >= -0.1)
            {
                return true;
            }
            else
            {
                return false;
            }
        break;
        case 2:
            axis1 = m_cubes[1][0][1].getCenter() - cubeCenter;
            if (glm::dot((center - m_cubes[1][0][1].getCenter()), axis1) <= 0.1 && glm::dot((center - m_cubes[1][0][1].getCenter()), axis1) >= -0.1)
            {
                return true;
            }
            else
            {
                return false;
            }
        break;
        case 3:
            axis1 = m_cubes[2][1][1].getCenter() - cubeCenter;
            if (glm::dot((center - m_cubes[2][1][1].getCenter()), axis1) <= 0.1 && glm::dot((center - m_cubes[2][1][1].getCenter()), axis1) >= -0.1)
            {
                return true;
            }
            else
            {
                return false;
            }
        break;
        case 4:
            axis1 = m_cubes[1][2][1].getCenter() - cubeCenter;
            if (glm::dot((center - m_cubes[1][2][1].getCenter()), axis1) <= 0.1 && glm::dot((center - m_cubes[1][2][1].getCenter()), axis1) >= -0.1)
            {
                return true;
            }
            else
            {
                return false;
            }
        break;
        case 5:
            axis1 = m_cubes[1][1][2].getCenter() - cubeCenter;
            if (glm::dot((center - m_cubes[1][1][2].getCenter()), axis1) <= 0.1 && glm::dot((center - m_cubes[1][1][2].getCenter()), axis1) >= -0.1)
            {
                return true;
            }
            else
            {
                return false;
            }
        break;
        default:
            return false;
        break;
    }
}

RubiksCube::~RubiksCube()
{

}
