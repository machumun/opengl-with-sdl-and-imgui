// in
uniform sampler2D u_positionTexture; // active 0
uniform sampler2D u_normalTexture; // active 1
uniform sampler2D u_albedoTexture; // active 2
in vec2 v_texCoord;

// out
layout (location = 0) out vec4 o_color; // framebuffer attachment 0
layout (location = 1) out vec4 o_bloom; // framebuffer attachment 1


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

void main(){

    vec4 normalTexture = texture2D(u_normalTexture, v_texCoord);
    vec3 norm = normalTexture.rgb;

    vec4 positionTexture = texture2D(u_positionTexture, v_texCoord);
    vec3 pos = positionTexture.rgb;

    vec4 albedoTexture = texture2D(u_albedoTexture, v_texCoord);
    
    

    

   
    if(albedoTexture.a > .0f){
        vec3 ambient = u_ambientLight.intensity*u_ambientLight.color;

        float a = 3.0f;
        float b = 0.7f;
        vec3 diffuse = vec3(.0f);

        for(int i = 0; i<POINT_LIGHT_NUM; ++i){
            vec3 lightVec = u_pointLight[i].position - pos;
            float lightDist = length(lightVec);
    
            float attenuation = 1.0f / ((a * lightDist + b) * lightDist + 1.0f);

            vec3 lightDir = normalize(lightVec);
            float diff = max(dot(norm, lightDir), .0f);

            diffuse += diff * u_pointLight[i].color * u_pointLight[i].intensity * attenuation;
        }

        vec4 result = vec4(ambient + diffuse, 1.f) * albedoTexture;
        o_color = result;
        float brightness = dot(result.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
        o_bloom = vec4(o_color.rgb * brightness, 1.f);

        // o_color = normalTexture;
    } else {
        o_color = vec4(.0f, .0f, .0f, 0.f);
        o_bloom = vec4(.0f, .0f, .0f, 0.f);
    }
    
    
    // float depth = logisticDepth(gl_FragCoord.z, 0.5f, 0.5f);
    // o_color = vec4(vec3(linearlizeDepth(gl_FragCoord.z) / far),1.0f);
    // o_color = result*(1.0f - depth) + vec4(depth * vec3(0.85f,0.85f,0.90f),1.0f);
    // o_color = vec4(1.0f,.0f,.0f,1.0f);

    // if(result.a>0){
    //     float brightness = dot(result.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
    //     o_bloom = vec4(o_color.rgb * brightness, 1.f);
    // }else{
    //     o_bloom = vec4(.0f, .0f, .0f, 0.f);
    // }
    


}