
#extension GL_ARB_explicit_attrib_location : require
layout ( location = 1 ) in vec3 position;
layout ( location = 2 ) in vec2 texCoord;
layout ( location = 3 ) in vec3 normal;
layout ( location = 7 ) in vec2 alphaTexCoord;

out vec4 pixelPos;
out vec3 norm;
out vec3 eyeNormal;
out vec4 vWorldPosition;
out vec4 vAdjustPosition;
out vec4 vLocalPosition;
out vec2 texCoord0;
out vec2 texCoord1;

uniform mat4 worldMatrix;
uniform mat4 invCameraMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vLocalPosition = vec4(position.xyz, 1);
	vWorldPosition = (modelViewMatrix * vLocalPosition);
	vAdjustPosition = (invCameraMatrix * modelViewMatrix) * vLocalPosition;
	gl_Position = projectionMatrix * vWorldPosition;
	pixelPos = gl_Position;

	// Lighting vectors
	
	norm = normal;
	eyeNormal = mat3(modelViewMatrix) * normal;
	
	texCoord0 = texCoord;
	texCoord1 = alphaTexCoord;
}
