varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;
struct BaseLight{
	vec3 color;
	float intensity;
};
struct DirectionalLight{
	BaseLight base;
	vec3 direction;
};
uniform vec3 eyePos;
uniform float specularIntensity;
uniform DirectionalLight directionalLight;
uniform sampler2D diffuse;
vec4 calcLight(BaseLight base, vec3 dir,vec3 normal){
	float diffuseFactor=dot(normal,-dir);
	vec4 diffuseColor=vec4(0.0,0.0,0.0,0.0);
	vec4 specularColor=vec4(0.0,0.0,0.0,0.0);
	if(diffuseFactor>0.0){
		diffuseColor=vec4(base.color,1.0)*base.intensity*diffuseFactor;
		vec3 directionToEye=normalize(eyePos-worldPos0);
		vec3 reflectDirection=normalize(reflect(dir,normal));
		//vec3 halfDirection=normalize(directionToEye-dir);
		//float specularFactor=dot(halfDirection,normal);
		float specularFactor=dot(directionToEye,reflectDirection);
		specularFactor=pow(specularFactor,4.0);
		if(specularFactor>0.0){
			specularColor=vec4(base.color,1.0)*specularIntensity *specularFactor;
		}
	}
	vec4 resultLight=diffuseColor + specularColor;
	return resultLight;
}
vec4 calcDirectionalLight(DirectionalLight dirLight,vec3 normal){
    return calcLight(dirLight.base,-dirLight.direction,normal);
} 
void main(){
    gl_FragColor=texture2D(diffuse,texCoord0.xy) * calcDirectionalLight(directionalLight,normalize(normal0));
}