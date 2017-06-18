
uniform float outlineValue;
uniform vec4 tintValue;
uniform float farClipPlane;
in vec3 eyeNormal;
in vec4 vWorldPosition;
uniform vec2 worldDimensions;


#extension GL_ARB_explicit_attrib_location: require

layout (location = 0) out vec4 albedoBuffer;
layout (location = 1) out vec4 normalBuffer;
layout (location = 2) out vec4 glowBuffer;
layout (location = 3) out vec4 specInteriorBuffer;

void WriteOutPositionAndNormals()
{
	vec3 norm = normalize(eyeNormal);
	normalBuffer.xyz = norm;			// FIXME packing?	
	normalBuffer.w = 1.0;
}

// c/o jamie owen https://github.com/jamieowen/glsl-blend

float blendColorDodge(float base, float blend) {
	return base / (1.0 - blend + (1.0 / 255.0));
}

vec3 blendColorDodge(vec3 base, vec3 blend) {
	return vec3(blendColorDodge(base.r,blend.r),blendColorDodge(base.g,blend.g),blendColorDodge(base.b,blend.b));
}

vec3 blendColorDodge(vec3 base, vec3 blend, float opacity) {
	return (blendColorDodge(base, blend) * opacity + base * (1.0 - opacity));
}