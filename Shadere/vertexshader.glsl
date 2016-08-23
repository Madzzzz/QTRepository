attribute vec3 aVertexPosition;
attribute vec4 aVertexColor;
attribute vec4 aVertexNormal;
uniform mat4 uMatrix;
   
attribute vec2 aTextureCoordinates;
varying vec2 vTextureCoordinates;

varying vec4 vColor;

void main(void) 
{
    gl_Position = uMatrix * vec4(aVertexPosition, 1.0);
    vColor = aVertexColor;
    //vTextureCoordinates = aTextureCoordinates;
}
