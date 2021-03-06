uniform vec3 camPos;
uniform sampler2D baseTex;
uniform sampler2D sideTex;
uniform sampler2D alphaTex;
varying vec4 pixelPos;

#define saturate(x) clamp(x,0.0,1.0)
#define lerp mix

uniform float ambient;
uniform float timer;

void main()
{
    vec3 foo = pixelPos.xyz;
	foo /= pixelPos.w;
	foo *= 0.5;
	foo += 0.5;	
	vec4 normalsDepth = texture(sideTex, foo.xy);

	vec4 pos;
	pos.x = pixelPos.x;
	pos.y = pixelPos.y;
	pos.z = (normalsDepth.w * 2.0 - 1.0);
	pos.w = 1;
	vec4 viewSpacePos = gl_ProjectionMatrixInverse * pos;
	viewSpacePos.xyz /= viewSpacePos.w;
	viewSpacePos.w = 1.0;
	vec4 worldSpacePos = gl_ModelViewMatrixInverse * viewSpacePos;

	// Now, reconstruct *my* position.

	pos.z = (pixelPos.z / pixelPos.w);
	viewSpacePos = gl_ProjectionMatrixInverse * pos;
	viewSpacePos.xyz /= viewSpacePos.w;
	viewSpacePos.w = 1.0;
	vec4 myWorldSpacePos = gl_ModelViewMatrixInverse * viewSpacePos;

	vec4 offsetTex = texture(alphaTex, foo.xy * 64.0 + vec2(timer,timer));
	offsetTex *= 2.0;
	offsetTex -= 1.0;
	float otherDistance = max(myWorldSpacePos.y - worldSpacePos.y, 0.0);
	vec4 tex = texture(baseTex, foo.xy + offsetTex.xy * 0.02 * otherDistance);
	
	float fog = saturate((myWorldSpacePos.y - worldSpacePos.y) / 4.0);
	fog = (fog) * 0.4;
	vec3 fogColor = vec3(0.2,0.1,0.07);
	gl_FragData[0].xyz = tex.xyz * (1.0 - fog) + fogColor * fog;
	gl_FragData[0].w = 1;


}
