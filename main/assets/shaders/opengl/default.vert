
uniform mat4 u_projectionMatrix;
uniform mat4 u_modelMatrix;

layout (location = 0) in vec3 a_vertexPosition;
layout (location = 1) in vec2 a_texCoord;
layout (location = 2) in vec3 a_normal;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_vertexPosition;

void main()
{
    gl_Position = u_projectionMatrix * u_modelMatrix * vec4(a_vertexPosition, 1.0);
    v_texCoord = a_texCoord;
}