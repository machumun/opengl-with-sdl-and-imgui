
uniform mat4 u_mvp;
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
    vec4 worldVertexPoisition = u_modelMatrix * vec4(a_vertexPosition, 1.0);
    vec4 worldVertexNormal = u_modelMatrix * vec4(a_normal, 1.0);

    gl_Position = u_projectionMatrix * worldVertexPoisition;
    v_texCoord = a_texCoord;
    // v_normal = (u_mvp * vec4(a_normal, 1.0)).xyz;
    v_normal = worldVertexNormal.xyz;
    v_vertexPosition = worldVertexPoisition.xyz;
}
