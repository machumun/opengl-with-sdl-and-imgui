// in
uniform sampler2D u_bloomTexture; //GL_COLOR_ATTACHMENT0
uniform bool horizontal = true;
uniform float loopNum = 1.f;

in vec2 v_texCoord;

layout (location = 0) out vec4 FragColor;

const int WEIGHT_NUM = 5;
float weight[WEIGHT_NUM] = float[](0.227027f, 0.1945946f, 0.1216216f, 0.054054f, 0.016216f);

void main()
{
    // texel
   vec2 tex_offset_delta = loopNum / textureSize(u_bloomTexture, 0);
   vec4 color = texture(u_bloomTexture, v_texCoord);
   vec3 result = color.rgb * weight[0];

   if(horizontal){
       for(int i = 1; i < WEIGHT_NUM; ++i){
           result += texture(u_bloomTexture, v_texCoord + vec2(tex_offset_delta.x * i, 0.0)).rgb * weight[i];
           result += texture(u_bloomTexture, v_texCoord - vec2(tex_offset_delta.x * i, 0.0)).rgb * weight[i];
       }
   }else{
        for(int i = 1; i < WEIGHT_NUM; ++i){
           result += texture(u_bloomTexture, v_texCoord + vec2(0.0, tex_offset_delta.y * i)).rgb * weight[i];
           result += texture(u_bloomTexture, v_texCoord - vec2(0.0, tex_offset_delta.y * i)).rgb * weight[i];
       }
   }

    // scale by brightness
   FragColor = vec4(result, 1.0f);
//    FragColor = texture(u_bloomTexture, v_texCoord);
    
}

