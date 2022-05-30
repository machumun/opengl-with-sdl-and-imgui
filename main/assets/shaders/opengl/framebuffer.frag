out vec4 FragColor;
in vec2 v_texCoords;

uniform sampler2D u_screenTexture; //color attachment 0
uniform sampler2D u_bloomTexture; // color attachment 1
uniform float gamma;

void main()
{
    vec3 fragment = texture(u_screenTexture, v_texCoords).rgb;
    vec3 bloom = texture(u_bloomTexture, v_texCoords).rgb;

    vec3 color = fragment + bloom;

    float exposure = 0.8f;
    vec3 toneMapped = vec3(1.0f) - exp(-color * exposure);

    // FragColor = vec4(pow(toneMapped, vec3(1.0f / gamma)), 1.f);


    FragColor = texture2D(u_screenTexture, v_texCoords);
    // FragColor = texture2D(u_bloomTexture, v_texCoords);
    // FragColor = vec4(1.0f, .0f, .0f, 1.0f);
}