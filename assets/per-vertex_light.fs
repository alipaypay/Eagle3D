varying vec2 texCoord0;
varying vec3 surfaceNormal;
varying vec3 toLightVector;
varying vec3 light_color;
uniform sampler2D diffuse;
void main(){
	vec3 unitNormal=normalize(surfaceNormal);
	vec3 unitLightVector=normalize(toLightVector);
	
	float nDot=dot(unitNormal,unitLightVector);
	
	float brightness=max(nDot,0.0);
	vec3 diffuseLight=brightness * light_color;
	gl_FragColor=vec4(diffuseLight,1.0) * texture(diffuse,texCoord0);
}