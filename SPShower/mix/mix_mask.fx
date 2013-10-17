sampler tex : register(S0);
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
	float4 tex_color = tex2D(tex, texCoord);

    return  (1 - tex_color.r) * tex2D(targetTex, texCoord);
}

float4 Main2(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float4 tex_color = tex2D(tex, texCoord);
	//tex_color.a = 1 - tex_color.a;
	return tex_color;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
	
	pass P1
	{
		PixelShader = compile ps_2_0 Main2();
	}
}