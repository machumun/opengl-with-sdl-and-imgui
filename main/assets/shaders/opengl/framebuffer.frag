uniform sampler2D u_screenTexture; //GL_COLOR_ATTACHMENT0
uniform sampler2D u_bloomTexture; //GL_COLOR_ATTACHMENT1

out vec4 FragColor;
in vec2 v_texCoord;

uniform float bloomIntensity;
uniform bool bloom;

float a = 2.51f, b = 0.03f, c = 2.43f, d = 0.59f, e = 0.14f;

void main()
{
    vec3 frag = texture(u_screenTexture, v_texCoord).rgb;
    vec3 blur = texture(u_bloomTexture, v_texCoord).rgb;

    

    // vec3 saturate = color*(a*color+vec3(b)) /  (color*(c*color+vec3(d)) + vec3(e));
    // vec3 toneMapped = vec3(1.0f) - exp(-color);
    // vec3 toneMapped = clamp(saturate, 0.0, 1.0);
    // clamp(a, 0.0, 1.0);

    if(bloom){

        vec3 color = frag + blur*bloomIntensity;

        // float luminance = dot(color, vec3(0.2126f, 0.7152f, 0.0722f));

        // vec3 toneMapped =  color / (1 + color);

        // vec3 result = pow(color, vec3(1.0f / gamma));

         vec3 result = color;

        if(result.r > 1.0 || result.g > 1.0 || result.b > 1.0){
            FragColor = vec4(1.0f, .0f, .0f, 1.0f);
        }else{
            FragColor = vec4(result, 1.0f);
        }

        FragColor = vec4(result, 1.0f);
        
        // FragColor = color;
        //  FragColor = texture2D(u_bloomTexture, v_texCoord);
    }else{
        // FragColor = texture2D(u_screenTexture, v_texCoord);
         FragColor = vec4(blur, 1.0f);
    }


}