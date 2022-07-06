uniform mat4 u_mvp;
uniform mat4 u_projectionMatrix;

layout (location = 0) in vec3 a_vertexPosition;
layout (location = 1) in vec2 a_texCoord;
layout (location = 2) in vec3 a_normal;

// out
out vec3 v_vertexPosition;
out vec3 v_normal;
out vec2 v_texCoord;

void main()
{
    vec4 worldVertexPoisition = vec4(a_vertexPosition, 1.0);

    // mat4 normalMatrix = transpose(inverse(u_modelMatrix));
    vec4 worldVertexNormal = vec4(.0f, .0f, .0f, .0f);

    gl_Position = u_projectionMatrix * worldVertexPoisition;

    v_texCoord = a_texCoord;
    v_normal = worldVertexNormal.xyz;
    v_vertexPosition = worldVertexPoisition.xyz;
}
