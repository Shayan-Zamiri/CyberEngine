#version 460

in vec2 v_TexCoords;

out vec4 f_Color;

uniform sampler2D texture_diffuse1;

void main()
{
  f_Color = texture(texture_diffuse1,v_TexCoords);
}