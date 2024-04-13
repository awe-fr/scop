#version 430 core

in vec4 UV;

out vec4 color;

uniform sampler2D myTextureSampler;

void main(){
  color = UV;
}