uniform sampler2D u_screenTexture; //GL_COLOR_ATTACHMENT0
uniform sampler2D u_bloomTexture; //GL_COLOR_ATTACHMENT1

out vec4 FragColor;
in vec2 v_texCoord;

uniform float gamma;
uniform bool bloom;

void main()
{
    vec3 fragment = texture(u_screenTexture, v_texCoord).rgb;
    vec3 blur = texture(u_bloomTexture, v_texCoord).rgb;

    vec3 color = fragment + blur;

    float exposure = 0.8f;
    vec3 toneMapped = vec3(1.0f) - exp(-color * exposure);

    if(bloom){
        FragColor.rgb = pow(toneMapped, vec3(1.0f / gamma));
        // FragColor = vec4(pow(color, vec3(1.0f / gamma)), 1.f);
    }else{
        FragColor = texture2D(u_screenTexture, v_texCoord);
    }

    


    // FragColor = texture2D(u_screenTexture, v_texCoord);
    // FragColor = texture2D(u_bloomTexture, v_texCoord);
    // FragColor = vec4(toneMapped, 1.f);

}