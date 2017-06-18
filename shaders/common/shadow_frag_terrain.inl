uniform sampler2D shadowTex;
uniform sampler2D gridTex;
uniform float shadowBias;
uniform vec4 uniformColor;

float pixelOffsetX = 0.5 / 2048.0;
float pixelOffsetY = 0.5 / 2048.0;



//Computes maximum error, depending on spatial shadow texel size projected to tangent plane
vec2 ComputeReceiverPlaneDepthBias(vec3 texCoordDX, vec3 texCoordDY)
{
	vec2 biasUV;
	biasUV.x = texCoordDY.y * texCoordDX.z - texCoordDX.y * texCoordDY.z;
	biasUV.y = texCoordDX.x * texCoordDY.z - texCoordDY.x * texCoordDX.z;

	biasUV /= (texCoordDX.x * texCoordDY.y) - (texCoordDX.y * texCoordDY.x);
	return biasUV;
}

vec4 getGrid ( vec4 bt, vec3 vAdjustedPosition, vec3 norm )
{
	vec4 gridTexel = texture(gridTex, texCoord1.xy);	
	// Test for the grid.
	float gridThresh = min(abs(4.0 - mod(abs(vAdjustedPosition.x + 4.0), 8.0)), abs(4.0 - mod(abs(vAdjustedPosition.z + 4.0), 8.0)));

	float gridAmt = 0.0;

	if (gridThresh < 0.20)
	{
		gridAmt = 1.0;
	}
	else if (gridThresh < 0.35)
	{
		gridAmt = 1.0 - (gridThresh - 0.2) / 0.15;
	}
	float gridAlpha = gridAmt * norm.y * norm.y;
	return lerp(bt, vec4(1.0, 1.0-gridTexel.r, 1.0-gridTexel.r, 1.0-gridTexel.r), gridAlpha * uniformColor.r);
}

float sampleShadowXY(sampler2D shadowMap, vec2 shadowCoord, float fragDepth)
{
	// shadow2DProj doesn't actually return the depth with hardware PCM enabled, eg GL_LINEAR filtering on the depth texture
	float shadowDepth = texture(shadowMap, shadowCoord).r;
	float depth = (fragDepth)/(shadowDepth);
	return depth > 1.0 ? 0.0 : 1.0;
}

float shadowMapOffset(vec4 lightCoords, vec2 offset )
{    	
	lightCoords.xy += offset * pixelOffsetX;
	float distance = lightCoords.z - 0.0004;
	return sampleShadowXY(shadowTex, lightCoords.xy,distance);
}

float shadowMap(vec4 lightCoords)
{
	return shadowMapOffset(lightCoords, vec2(0.0,0.0));
}

float PCFShadowMap( vec4 lightCoords )
{	
	vec3 dTex_dX = dFdx(lightCoords.xyz);
	vec3 dTex_dY = dFdy(lightCoords.xyz);

	dTex_dX.xy*=0.5*vec2(1,-1);
	dTex_dY.xy*=0.5*vec2(1,-1);

	vec2 receiverPlaneDepthBias = ComputeReceiverPlaneDepthBias(dTex_dX, dTex_dY);
	float fractionalSamplingError = dot(vec2(pixelOffsetX, pixelOffsetY), abs(receiverPlaneDepthBias));

	float shadow = 0.0;

	float x,y;
	
	// -4.5 -3.5 -2.5 -1.5 -0.5 0.5 1.5 2.5 3.5 4.5	
	float distance = lightCoords.z;

	for (y = -3.5 ; y <= 3.5 ; y+=1.0)
	{
		for (x = -3.5 ; x <= 3.5 ; x+=1.0)
		{			
			float shadowDepth = textureGrad(shadowTex, lightCoords.xy + vec2(x,y) * pixelOffsetX, dTex_dX.xy, dTex_dY.xy).r;
			float depth = (distance)/(shadowDepth);
			shadow += (depth > 1.0 ? 0.0 : 1.0);
//			shadow += shadowMapOffset(lightCoords, vec2(x,y) * );
		}
	}
	shadow /= 64.0;

//	lightCoords.xy += offset * pixelOffsetX;

	
//	shadow = depth > 1.0 ? 0.0 : 1.0;
		// return sampleShadowXY(shadowTex, lightCoords.xy,distance);

	/*
	shadow = shadowMapOffset(lightCoords,vec2(0,0));
	return g_txShadow.SampleGrad( g_samShadowLinearClamp, tex, dTex_dX.xy, dTex_dY.xy).x > (fragDepth-EPSILON-fractionalSamplingError);
	*/

	
	return shadow;
}
