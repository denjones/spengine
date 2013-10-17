sampler tex : register(S0);
texture Tex1;
float width  : register(C0);
float height : register(C1);
float transitionPosition : register(C2);
float level : register(C3);
float opacity : register(C4);

sampler effectTex = sampler_state
{
	Texture = (Tex1);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

float4 Main(float4 color : COLOR, float2 texCoord : TEXCOORD0) : COLOR
{
	float4 tex_color = tex2D( tex , texCoord);    
	float4 shadow_color =  tex2D(effectTex , texCoord); 
    
    float ix = 1.0 / width;
    float iy = 1.0 / height;
    
    int i;
	float4 targetColor = tex2D(tex, texCoord + float2(- level * ix, - level * iy));

	if(targetColor.a > 0) 
	{
		shadow_color.a = targetColor.a * opacity;
		return shadow_color * color; 
	}

	return 0 ;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}