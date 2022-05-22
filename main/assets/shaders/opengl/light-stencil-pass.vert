
uniform mat4 u_mvp;


attribute vec3 a_vertexPosition;

void main()
{
    gl_Position = u_mvp * vec4(a_vertexPosition, 1.0);
}