// uniformは4x4行列
uniform mat4 mvp;

// input処理でユーザから受け取る情報
attribute vec3 vertexPosition;

// 頂点シェーダから値を渡す
varying vec4 fragmentColor;

void main(){
    gl_Position = mvp*vec4(vertexPosition,1.0);
    fragmentColor = vec4(1.0,1.0,1.0,1.0);
}