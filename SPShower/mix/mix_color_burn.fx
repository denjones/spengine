////////////////////////////////////////////////
// Name: mix_color_burn.mm
// Author:方枫杰
// Date:2012-8-13
// Desc:颜色加深，查看每个通道中的颜色信息,
// 通过增加对比度使基色变暗以反映混合色，与黑色混合后不产生变化。
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

	out_color.r = 1 - (1 - target_tex_color.r) / tex_color.r;
	out_color.g = 1 - (1 - target_tex_color.g) / tex_color.g;
	out_color.b = 1 - (1 - target_tex_color.b) / tex_color.b;
    
	return out_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}