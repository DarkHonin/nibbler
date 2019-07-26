#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec4 pos;

void main()
{
    gl_Position = pos + vec4(aPos.x, aPos.y, aPos.z, 1.0);
}