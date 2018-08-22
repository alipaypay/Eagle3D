varying vec2 texCoord0;
uniform sampler2D sampler;
uniform vec3 ambientIntensity;
void main(){
    
    gl_FragColor=texture2D(sampler,texCoord0.xy)*vec4(ambientIntensity,1.0);
    
}