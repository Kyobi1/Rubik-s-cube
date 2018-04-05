#include "maths.h"

#include <iostream>



glm::vec3 rotation(float angle, glm::vec3 rot, glm::vec3 vec)
{
    glm::mat3 matRotate;
    float angleRad = degToRad(angle);
    float c = cos(angleRad), s = sin(angleRad);

    matRotate[0][0] = rot.x*rot.x*(1-c) + c;
    matRotate[0][1] = rot.x*rot.y*(1-c) - rot.z*s;
    matRotate[0][2] = rot.x*rot.z*(1-c) + rot.y*s;
    matRotate[1][0] = rot.x*rot.y*(1-c) + rot.z*s;
    matRotate[1][1] = rot.y*rot.y*(1-c) + c;
    matRotate[1][2] = rot.y*rot.z*(1-c) - rot.x*s;
    matRotate[2][0] = rot.x*rot.z*(1-c) - rot.y*s;
    matRotate[2][1] = rot.y*rot.z*(1-c) + rot.x*s;
    matRotate[2][2] = rot.z*rot.z*(1-c) + c;

    glm::vec3 coord = matRotate * vec;

    return coord;
}

float degToRad(float angle)
{
    return angle*M_PI/180;
}

float radToDeg(float angle)
{
    return angle*180/M_PI;
}
