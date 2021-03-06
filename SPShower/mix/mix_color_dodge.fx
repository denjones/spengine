////////////////////////////////////////////////
// Name: mix_color_dodge.mm
// Author:方枫杰
// Date:2012-8-13
// Desc:颜色减淡，查看每个通道中的颜色信息，
// 并通过减小对比度使基色变亮以反映混合色，与黑色混合则不发生变化。
///////////////////////////////////////////////

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
	float4 target_tex_color = tex2D(targetTex, texCoord);

	float4 out_color = target_tex_color;

	if(tex_color.r == 1)
		out_color.r = 1;
	else
		out_color.r = target_tex_color.r  / (1 - tex_color.r);
	
	if(tex_color.g == 1)
		out_color.g = 1;
	else
		out_color.g = target_tex_color.g  / (1 - tex_color.g);
	
	if(tex_color.b == 1)
		out_color.b = 1;
	else
		out_color.b = target_tex_color.b  / (1 - tex_color.b);
    
	return out_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}