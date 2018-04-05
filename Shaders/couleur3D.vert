#version 150 core

in vec3 in_vertex;
in vec3 in_colors;

uniform mat4 modelviewProjection;

out vec3 color;

void main()
{
    gl_Position = modelviewProjection * vec4(in_vertex, 1.0);

    color = in_colors;
}
