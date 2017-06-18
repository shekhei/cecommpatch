
vec4 piecewiseBlend(vec4 upperTex, vec4 lowerTex, float amount)
{
/*
	const float blendRange = 0.1;
	vec4 baseTexel;
	
	amount *= 1.0 + blendRange;
	
	if (upperTex.a < amount - blendRange) 
	{
		baseTexel = upperTex;
	} 
	else if (upperTex.a > amount + blendRange) 
	{
		baseTexel = lowerTex;
	} 
	else 
	{
		float f = (upperTex.a - (amount - blendRange)) / (2.0 * blendRange);
		baseTexel = lerp(upperTex, lowerTex, f);	
	}	
	
	return baseTexel;
	*/
	
	return lerp(lowerTex, upperTex, amount);
}
