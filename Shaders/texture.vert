#version 150 core

in vec3 in_vertex;
in vec2 in_texCoord0;

uniform mat4 modelviewProjection;

out vec2 coordTex0;

void main()
{
    gl_Position = modelviewProjection * vec4(in_vertex, 1.0);

    coordTex0 = in_texCoord0;
}
