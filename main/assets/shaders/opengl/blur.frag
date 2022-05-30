uniform sampler2D u_screenTexture; //GL_COLOR_ATTACHMENT0

layout (location = 0) out vec4 FragColor;

uniform bool horizontal = true;
uniform float weight[5] = float[](0.227027f, 0.1945946f, 0.1216216f, 0.054054f, 0.016216f);

in vec2 v_texCoord;

void main()
{
//    vec2 tex_offset = 1.0f / textureSize(u_screenTexture, 0);
//    vec3 result = texture(u_screenTexture, v_texCoord).rgb * weight[0];

//    if(horizontal){
//        for(int i = 1; i < 5; ++i){
//            result += texture(u_screenTexture, v_texCoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
//            result += texture(u_screenTexture, v_texCoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
//        }
//    }else{
//         for(int i = 1; i < 5; ++i){
//            result += texture(u_screenTexture, v_texCoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
//            result += texture(u_screenTexture, v_texCoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
//        }
//    }

//    FragColor = vec4(result, 1.0f);
    FragColor = texture2D(u_screenTexture, v_texCoord);
    // FragColor = vec4(1.0f, .0f, .0f, 1.0f);
    
}

