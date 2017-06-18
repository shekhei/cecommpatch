[Vertex shader]

// these will be generated once per light

uniform vec3 lightPos;
uniform vec3 lightDir;
varying vec4 distanceFromLight;
uniform float lightRadius;

// for instance (these are directional lights)

uniform vec3 lightPos2;
uniform vec3 lightDir2;
varying vec4 distanceFromLight2;
varying vec4 ProjShadow;

varying vec3 norm;
varying vec3 view;
uniform vec3 scaleFactor;
uniform mat4 worldMatrix;
varying vec4 pixelPos;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	pixelPos = gl_Position;
	gl_TexCoord[0] = gl_Vertex;
}
