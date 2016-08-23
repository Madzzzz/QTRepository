precision mediump float;

varying vec4 vColor;
uniform sampler2D uSampler;
varying vec2 vTextureCoordinates;

void main(void) 
{
    gl_FragColor = vColor;
    //gl_FragColor = texture2D(uSampler, vTextureCoordinates);
}        
