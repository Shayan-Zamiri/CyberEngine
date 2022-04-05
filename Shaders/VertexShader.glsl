#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;

out vec2 v_TexCoords;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
  v_TexCoords = TexCoords;
  gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(VertexPosition,1);
}
