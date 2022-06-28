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


void main()
{
    vec4 color =  texture2D(u_sampler, v_texCoord) * vec4(u_baseColor, 1.f);
    u_positionTexture = vec4(v_vertexPosition, color.a);
    u_normalTexture = vec4(normalize(v_normal), color.a);
    u_albedoTexture = color;
    // u_albedoTexture = vec4(1.f, .0f, .0f, 1.f);

}

