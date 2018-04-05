#ifndef DEF_MATHS
#define DEF_MATHS

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 rotation(float angle, glm::vec3 rot, glm::vec3 vec);
float degToRad(float angle);
float radToDeg(float angle);

#endif // DEF_MATHS
