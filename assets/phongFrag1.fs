varying vec2 texCoord0;
varying vec3 normal0;
//3.
//struct BaseLight{
//	vec3 color;
//	float intensity;
//};
//struct DirectionalLight{
//	BaseLight base;
//	vec3 direction;
//};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//struct Attenuation{
//	float constant;
//	float linear;
//	float exponent;
//};
//struct PointLight{
//BaseLight base;
//Attenuation atten;
//vec3 position;
//}
//const int MAX_POINT_LIGHTS=4;
//uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec4 calcPointLight(PointLight pointLight,vec3 normal){
	vec3 lightDirection=worldPos0-pointLight.position;
	float distanceToPoint=length(lightDirection);
	lightDirection=normalize(lightDirection);
	vec4 color=calcLight(pointLight.base,lightDirection,normal);
	float attenutation=pointLight.atten.constant+
						pointLight.atten.linear*distanceToPoint+
						pointLight.atten.exponent*distanceToPoint*distanceToPoint+
						0.0001;
    return color/attenutation;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//uniform DirectionalLight dirLight;
uniform sampler2D sampler;
uniform vec3 ambientLight;
uniform vec3 baseColor;

uniform vec3 color;
uniform float intensity;
uniform vec3 direction;
//2.
//vec4 calcLight(BaseLight base,vec3 direction,vec3 normal){

//	float diffuseFactor=dot(normal,-direction);
	
//	vec4 diffuseColor=vec4(0,0,0,0);
//	if(diffuseFactor>0.0){
//		diffuseColor=vec4(base.color,1.0)*base.intensity*diffuseFactor;
//	}
//	return diffuseColor;
//}
//1.
//vec4 calcDirectionalLight(DirectionalLight dirLight,vec3 normal){


//    return calcLight(dirLight.base,-dirLight.direction,normal);

//} 

vec4 calcLight(vec3 direction,vec3 normal){

	float diffuseFactor=dot(normal,-direction);
	
	vec4 diffuseColor=vec4(0,0,0,0);
	if(diffuseFactor>0.0){
		diffuseColor=vec4(color,1.0)*intensity*diffuseFactor;
	}
	return diffuseColor;
}

vec4 calcDirectionalLight(vec3 normal){


    return calcLight(-direction,normal);

} 

void main(){
    vec4 totalLight=vec4(ambientLight,1.0);
    vec4 textureColor = texture2D(sampler,texCoord0.xy);
    vec4 color =vec4(baseColor,1.0);
   	color*=textureColor;
   	
   	vec3 normal=normalize(normal0);
   	//4.
   //	totalLight+=calcDirectionalLight(dirLight,normal);
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PointLight~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   
   
   
   
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   
   
   	totalLight+=calcDirectionalLight(normal);
	for(int i=0;i<MAX_POINT_LIGHTS;i++){
	totalLight+=calcPointLight(pointLights[i],normal);
   }
    gl_FragColor=color * totalLight;
}