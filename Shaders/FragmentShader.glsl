#version 460

out vec4 v_Color;

uniform vec4 u_Color;

void main()
{
  v_Color = u_Color;
}