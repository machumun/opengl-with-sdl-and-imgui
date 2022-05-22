
uniform sampler2D u_sampler;

uniform vec3 u_pointLightPosition;
uniform vec4 u_pointLightColor;
uniform float u_pointLightStrength;
uniform vec4 u_ambientLightColor;
uniform float u_ambientLightStrength; 

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_vertexPosition;

// in vec4 gl_FragCoord;
// in bool gl_FrontFacing;
// in vec2 gl_PointCoord;

out vec4 FragColor;

float near = 0.01f;
float far = 100.0f;

float linearlizeDepth(float depth){
    return (2.0f * near * far) / (far + near - (depth * 2.0f - 1.0f) * (far - near));
}

float logisticDepth(float depth, float steepness, float offset){
    float zVal = linearlizeDepth(depth);
    return (1 / (1 + exp(- steepness * (zVal - offset))));
    return 0.5f;
}

void main()
{
    vec4 ambient = u_ambientLightStrength*u_ambientLightColor;

    vec3 norm = normalize(v_normal);

    vec3 lightVec = u_pointLightPosition - v_vertexPosition;
    float lightDist = length(lightVec);
    float a = 3.0f;
    float b = 0.7f;
    float attenuation = 1.0f / (a*lightDist*lightDist + lightDist*b + 1.0f);
    // Attenuation coefficient of light
    

    vec3 lightDir = normalize(lightVec);
    float diff = max(dot(norm,lightDir),0.0f);
    vec4 diffuse = diff*u_pointLightColor*u_pointLightStrength;

    vec4 result = (ambient+diffuse*attenuation)*texture2D(u_sampler, v_texCoord);

    FragColor = result;
    // float depth = logisticDepth(gl_FragCoord.z, 0.5f, 0.5f);
    // FragColor = vec4(vec3(linearlizeDepth(gl_FragCoord.z) / far),1.0f);
    // FragColor = result*(1.0f - depth) + vec4(depth * vec3(0.85f,0.85f,0.90f),1.0f);
    // FragColor = vec4(1.0f,.0f,.0f,1.0f);
}

