// in
uniform sampler2D u_sampler;
uniform vec3 u_baseColor = vec3(1.f,1.f,1.f);

in vec3 v_vertexPosition;
in vec3 v_normal;
in vec2 v_texCoord;


// out
layout (location = 0) out vec4 u_positionTexture; // framebuffer attachment 0
layout (location = 1) out vec4 u_normalTexture; // framebuffer attachment 1
layout (location = 2) out vec4 u_albedoTexture; // framebuffer attachment 2


uniform vec2 u_currentOffsetUV = vec2(1.f, .0f);
uniform vec2 u_spliteNum = vec2(.0f, .0f);


// const int unitNumX = 6;
// const int unitNumY = 4;

// const float texCoordOffsetsX[unitNumX] = float[](.0f, 0.16667f, 0.33333f, 0.5f, 0.66667f, 0.83333f);
// const float texCoordOffsetsY[unitNumY] = float[](.0f, .25f, .5f, .75f);


void main()
{
    vec2 animatedUV = v_texCoord / u_spliteNum + u_currentOffsetUV;
    vec4 color =  texture2D(u_sampler, animatedUV) * vec4(u_baseColor, 1.f);
    u_positionTexture = vec4(v_vertexPosition, color.a);
    u_normalTexture = vec4(normalize(v_normal), color.a);
    u_albedoTexture = color;
}

