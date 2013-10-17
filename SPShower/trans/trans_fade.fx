sampler tex : register(S0);
extern float transitionPosition : register(C2);
texture Tex1;

sampler targetTex = sampler_state
{
	Texture = (Tex1);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};


float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float pos = transitionPosition;
	float4 texColor = tex2D(tex, texCoord);
	float4 targetColor = tex2D(targetTex, texCoord);

    return targetColor * pos + texColor * (1 - pos);
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}