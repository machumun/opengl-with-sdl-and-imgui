uniform sampler2D u_sampler;
uniform vec3 u_baseColor = vec3(1.f,1.f,1.f);

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BloomColor;

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_vertexPosition;

const int POINT_LIGHT_NUM = 1;

struct AmbientLight{
    vec3 color;
    float intensity;
};

struct PointLight{
    vec3 position;
    vec3 color;
    float intensity;
};

uniform AmbientLight u_ambientLight;
uniform PointLight u_pointLight[POINT_LIGHT_NUM];

float near = 0.01f;
float far = 100.0f;

const vec2 frameNum = vec2(4, 4);
uniform int frame = 0;

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
    vec2 offset = vec2(mod(frame, frameNum.x), abs(frame / frameNum.x));

    vec2 delta = 1 / frameNum;
    vec2 origin = v_texCoord / frameNum;

    vec2 offset_texCoord = dot(delta, offset) + origin;

    vec3 ambient = u_ambientLight.intensity*u_ambientLight.color;

    vec3 norm = normalize(v_normal);


    float a = 3.0f;
    float b = 0.7f;

    vec3 diffuse = vec3(.0f);
    
    for(int i = 0; i<POINT_LIGHT_NUM; ++i){
        vec3 lightVec = u_pointLight[i].position - v_vertexPosition;
        float lightDist = length(lightVec);
    
        float attenuation = 1.0f / ((a*lightDist + b)*lightDist + 1.0f);

        vec3 lightDir = normalize(lightVec);
        float diff = max(dot(norm,lightDir),0.0f);

        diffuse += diff*u_pointLight[i].color*u_pointLight[i].intensity*attenuation;
    }

    
    vec4 result = vec4(ambient+diffuse, 1.f)*texture2D(u_sampler, offset_texCoord)*vec4(u_baseColor, 1.f);

    FragColor = result;

    if(result.a>0){
        float brightness = dot(result.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
        BloomColor = vec4(FragColor.rgb * brightness, 1.f);
    }else{
        BloomColor = vec4(.0f, .0f, .0f, 0.f);
    }

}

