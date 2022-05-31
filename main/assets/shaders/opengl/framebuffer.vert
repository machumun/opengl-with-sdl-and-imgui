layout (location = 0) in vec2 a_vertexPosition; 
layout (location = 1) in vec2 a_texCoord; 

out vec2 v_texCoord;

void main()
{
    gl_Position = vec4(a_vertexPosition.x, a_vertexPosition.y, .0f, 1.0f); 
    v_texCoord = a_texCoord;
}  