#version 460

layout(location = 0) in vec3 v_VertexPosition;

out vec3 v_Position;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
  v_Position = vec4(u_ModelMatrix * vec4(v_VertexPosition,1.0f)).xyz;
  gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(v_VertexPosition,1);
}