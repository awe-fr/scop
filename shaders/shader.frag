#version 430 core

in vec4 UV;

out vec4 color;

uniform sampler2D myTextureSampler;
uniform float trans;

void main(){
  vec4 colort = vec4(0.0, 0.0, 1.0, 1.0);
  color = mix(UV, colort, smoothstep(0.0, 1.0, trans));
}