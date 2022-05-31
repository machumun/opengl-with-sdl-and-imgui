uniform sampler2D u_bloomTexture; //GL_COLOR_ATTACHMENT0

layout (location = 0) out vec4 FragColor;

uniform bool horizontal = true;
uniform float weight[5] = float[](0.227027f, 0.1945946f, 0.1216216f, 0.054054f, 0.016216f);

in vec2 v_texCoord;

void main()
{

   vec2 tex_offset = 1.0f / textureSize(u_bloomTexture, 0);
   vec4 result = texture(u_bloomTexture, v_texCoord) * weight[0];

   if(horizontal){
       for(int i = 1; i < 5; ++i){
           result += texture(u_bloomTexture, v_texCoord + vec2(tex_offset.x * i, 0.0)) * weight[i];
           result += texture(u_bloomTexture, v_texCoord - vec2(tex_offset.x * i, 0.0)) * weight[i];
       }
   }else{
        for(int i = 1; i < 5; ++i){
           result += texture(u_bloomTexture, v_texCoord + vec2(0.0, tex_offset.y * i)) * weight[i];
           result += texture(u_bloomTexture, v_texCoord - vec2(0.0, tex_offset.y * i)) * weight[i];
       }
   }

   FragColor = result;
    
}

