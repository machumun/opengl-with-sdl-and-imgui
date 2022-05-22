uniform sampler2D u_sampler;

in vec2 v_texCoord;


out vec4 FragColor;

void main()
{
    // gl_FragColor = texture2D(u_sampler, v_texCoord);
    FragColor = vec4(1.0f,1.0f,1.0f,1.0f); 
}