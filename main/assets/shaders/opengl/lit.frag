uniform sampler2D u_sampler;

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

    
    

    vec4 result = vec4(ambient+diffuse, 1.f)*texture2D(u_sampler, v_texCoord);

    
    // float depth = logisticDepth(gl_FragCoord.z, 0.5f, 0.5f);
    // FragColor = vec4(vec3(linearlizeDepth(gl_FragCoord.z) / far),1.0f);
    // FragColor = result*(1.0f - depth) + vec4(depth * vec3(0.85f,0.85f,0.90f),1.0f);
    // FragColor = vec4(1.0f,.0f,.0f,1.0f);

    FragColor = result;
    // FragColor.a = 1;

    // BloomColor = result;

    // if(result.r > 0.05f){
    //     result.r *= 5.0f;
    // }
    //  if(result.g > 0.05f){
    //     result.g *= 5.0f;
    // }
    //  if(result.b > 0.05f){
    //     result.b *= 5.0f;
    // }

    
    BloomColor = result;
    float brightness = dot(result.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
    // BloomColor.a = brightness*1.f;
    // BloomColor.a = brightness;
    BloomColor = FragColor*brightness;
    // if(brightness > 1.0f){
    //     BloomColor = FragColor*brightness;
    // }else{
    //     BloomColor = vec4(.0f, .0f, .0f, 1.f);
    // }
}

