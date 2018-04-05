#version 150 core

in vec2 coordTex0;

uniform sampler2D tex0;

out vec4 out_color;

void main()
{
    out_color = texture(tex0, coordTex0);
}
