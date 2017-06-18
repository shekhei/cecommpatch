
#extension GL_ARB_explicit_attrib_location : enable
layout ( location = 1 ) in vec3 position;
layout ( location = 2 ) in vec2 texCoord;
layout ( location = 3 ) in vec3 normal;
layout ( location = 4 ) in vec4 color; 
layout ( location = 5 ) in vec4 blendIndices;
layout ( location = 6 ) in vec4 blendWeights;
layout ( location = 7 ) in vec2 alphaTexCoord;

uniform mat4 worldMatrix;
uniform mat4 invCameraMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 cameraNormalMatrix;
