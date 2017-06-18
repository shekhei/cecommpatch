uniform sampler2D sideTex;
vec4 GetLightAmbient()
{
	vec4 realWorldPos = invCameraMatrix * vWorldPosition;
	vec2 interiorLookUp = (realWorldPos.xz / worldDimensions / 8.0) + vec2(0.5, 0.5);		
	vec4 interiorSample = texture(sideTex, interiorLookUp);
	return mix(lightAmbient, vec4(0.5,0.5,0.5,1.0), interiorSample.w);
}

float GetInteriorSample()
{
	vec4 realWorldPos = invCameraMatrix * vWorldPosition;
	vec2 interiorLookUp = (realWorldPos.xz / worldDimensions / 8.0) + vec2(0.5, 0.5);		
	vec4 interiorSample = texture(sideTex, interiorLookUp);
	return interiorSample.w;
}
