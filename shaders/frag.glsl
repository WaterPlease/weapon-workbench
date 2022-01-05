#version 330 core

in vec3 fNormal;
in vec2 fTexcoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
   FragColor = texture(texture1, fTexcoord);//#ourColor;
}