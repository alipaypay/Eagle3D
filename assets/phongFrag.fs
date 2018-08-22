varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;
//const int MAX_POINT_LIGHTS=1;
//const int MAX_SPOT_LIGHTS=1;
struct BaseLight{
	vec3 color;
	float intensity;
};
struct DirectionalLight{
	BaseLight base;
	vec3 direction;
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
uniform DirectionalLight directionalLight;
uniform float specularIntensity;
uniform sampler2D sampler;
uniform vec3 ambientLight;
uniform vec3 baseColor;
//uniform PointLight pointLights[MAX_POINT_LIGHTS];
//uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
vec4 calcLight(BaseLight base, vec3 dir,vec3 normal){
	float diffuseFactor=dot(normal,-dir);
	vec4 diffuseColor=vec4(0.0,0.0,0.0,0.0);
	vec4 specularColor=vec4(0.0,0.0,0.0,0.0);
	if(diffuseFactor>0.0){
		diffuseColor=vec4(base.color,1.0)*base.intensity*diffuseFactor;
		vec3 directionToEye=normalize(eyePos-worldPos0);
		
		vec3 reflectDirection=normalize(reflect(dir,normal));
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
    return calcLight(dirLight.base,dirLight.direction,normal);
} 

//vec4 calcPointLight(PointLight pointLight,vec3 normal){
//	vec3 p=pointLight.position;
//	vec3 lightDirection=worldPos0-vec3(-2.0,0.0,3.0);
//	float distanceToPoint=length(lightDirection);
//  if(distanceToPoint>pointLight.range){
//	return vec4(0.0,0.0,0.0,0.0);
//	}
//	lightDirection=normalize(lightDirection);
//	vec4 color=calcLight(pointLight.base,lightDirection,normal);
//	float attenutation=pointLight.atten.constant+
//						pointLight.atten.linear*distanceToPoint+
//						pointLight.atten.exponent*distanceToPoint*distanceToPoint+
//						0.0001;
//    return color/attenutation;
//}

//vec4 calcSpotLight(SpotLight spotLight,vec3 normal){
//	vec3 lightDirection=normalize(worldPos0-spotLight.pointLight.position);
//	float spotFactor=dot(lightDirection,spotLight.direction);
//	vec4 color=vec4(0.0,0.0,0.0,0.0);
//	if(spotFactor>spotLight.cutoff){
//		color=calcPointLight(spotLight.pointLight,normal)*
//		(1.0-(1.0-spotFactor)/(1.0-spotLight.cutoff))
//		;
//	}
//	return color;
	
//}


void main(){
    vec4 totalLight=vec4(ambientLight,1.0);
    vec4 textureColor = texture2D(sampler,texCoord0.xy);
    vec4 color =vec4(baseColor,1.0);
   	color*=textureColor;
   	
   	vec3 normal=normalize(normal0);
   
   	totalLight+=calcDirectionalLight(directionalLight,normal);

	//for(int i=0;i<MAX_POINT_LIGHTS;i++){
	//  if(pointLights[i].base.intensity>0.0){
	//	totalLight+=calcPointLight(pointLights[i],normal);
	//}
	//}
	//for(int i=0;i<MAX_SPOT_LIGHTS;i++){
	//  if(spotLights[i].pointLight.base.intensity>0.0){
	//		totalLight+=calcSpotLight(spotLights[i],normal);
	//}
	//}
	
	
    gl_FragColor=color * totalLight;
}