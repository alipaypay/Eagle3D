varying vec2 texCoord0;
uniform sampler2D sampler;
uniform vec3 color;
void main(){
    vec4 textureColor = texture2D(sampler,texCoord0.xy);
    gl_FragColor=textureColor*vec4(color,1.0);
    
}