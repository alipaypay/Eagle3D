attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 surfaceNormal;
varying vec3 toLightVector;
varying vec3 light_color;

uniform mat4 model;
uniform mat4 MVP;
uniform vec3 lightColor;
uniform vec3 lightPosition;
void main(){
	light_color=lightColor;
    texCoord0=texCoord;
    surfaceNormal=(model*vec4(normal,0.0)).xyz;
	surfaceNormal=normalize(surfaceNormal);
	vec3 worldPos0=(model*vec4(position,1.0)).xyz;
	toLightVector=lightPosition-worldPos0;
	gl_Position=MVP*vec4(position,1.0);
}