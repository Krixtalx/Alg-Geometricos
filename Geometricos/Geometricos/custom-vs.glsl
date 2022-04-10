// VERTEX SHADER
#version 410

layout (location = 0) in vec3 posicion;

uniform mat4 matrizMVP;

void main ()
{
   gl_Position = matrizMVP * vec4 ( posicion, 1 );
}