varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;

struct BaseLight{
	vec3 color;
	float intensity;
};

struct Attenuation{
 float constant;
 float linear;
 float exponent;
};

struct PointLight{
 BaseLight base;
 Attenuation atten;
 vec3 position;
 float range;
};


struct SpotLight{
	PointLight pointLight;
	vec3 direction;
	float cutoff;

};

uniform vec3 eyePos;
uniform float specularIntensity;
uniform sampler2D diffuse;

uniform SpotLight spotLight;

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


vec4 calcPointLight(PointLight pointLight,vec3 normal){
	vec3 p=pointLight.position;
	vec3 lightDirection=worldPos0-vec3(-2.0,0.0,3.0);
	float distanceToPoint=length(lightDirection);
    if(distanceToPoint>pointLight.range){
	   return vec4(0.0,0.0,0.0,0.0);
	}
	lightDirection=normalize(lightDirection);
	vec4 color=calcLight(pointLight.base,lightDirection,normal);
	float attenutation=pointLight.atten.constant+
						pointLight.atten.linear*distanceToPoint+
						pointLight.atten.exponent*distanceToPoint*distanceToPoint+
						0.0001;
    return color/attenutation;
}

vec4 calcSpotLight(SpotLight spotLight,vec3 normal){
	vec3 lightDirection=normalize(worldPos0-spotLight.pointLight.position);
	float spotFactor=dot(lightDirection,spotLight.direction);
	vec4 color=vec4(0.0,0.0,0.0,0.0);
	if(spotFactor>spotLight.cutoff){
		color=calcPointLight(spotLight.pointLight,normal)*
		(1.0-(1.0-spotFactor)/(1.0-spotLight.cutoff));
	}
	return color;
	
}

void main(){
    gl_FragColor=texture2D(diffuse,texCoord0.xy) * calcSpotLight(spotLight,normalize(normal0));
}