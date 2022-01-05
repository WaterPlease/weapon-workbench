#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec2 iTexcoord;
layout (location = 2) in vec3 iNormal;

uniform mat4 transform;
uniform mat4 view;

out vec3 fNormal;
out vec2 fTexcoord;

void main()
{
   fNormal = iNormal;
   fTexcoord = iTexcoord;
   gl_Position = view * transform * vec4(iPos.xyz, 1.0);
}