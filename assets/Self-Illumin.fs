varying vec2 texCoord0;
uniform sampler2D sampler;
uniform vec3 selfIlluminIntensity;
void main(){
    
    gl_FragColor=texture2D(sampler,texCoord0.xy)*vec4(selfIlluminIntensity,1.0);
    
}