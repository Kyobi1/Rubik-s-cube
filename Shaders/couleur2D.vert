#version 150 core

in vec2 in_vertex;
in vec3 in_colors;

out vec3 color;

void main()
{
    gl_Position = vec4(in_vertex, 0.0, 1.0);

    color = in_colors;
}
