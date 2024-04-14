#version 430 core

in vec4 UV;
in vec2 coor;

out vec4 color;

uniform sampler2D tex;
uniform float trans;

void main(){
  vec4 texture = texture(tex, coor);
  color = mix(UV, texture, smoothstep(0.0, 1.0, trans));
}