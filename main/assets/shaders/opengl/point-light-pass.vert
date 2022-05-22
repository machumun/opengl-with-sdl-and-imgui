
uniform mat4 u_mvp;

// layout (binding = 0) uniform sampler2D GBuffer0;
// layout (binding = 1) uniform sampler2D GBuffer1;
// layout (binding = 2) uniform sampler2D GBuffer2;

uniform vec3 worldLightPosition;
uniform float lightIntensity; // lm
uniform vec3 lightColor;
uniform float lightRange;

uniform vec3 worldCameraPos;
uniform mat4 ViewProjectionI;
uniform vec2 ProjectionParams; // x: near, y: far

attribute vec3 a_vertexPosition;

// vec2 CalcTexCoord()
// {
//    return gl_FragCoord.xy / textureSize(GBuffer0, 0);
// }

void main()
{
    gl_Position = u_mvp * vec4(a_vertexPosition, 1.0);
}