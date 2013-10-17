////////////////////////////////////////////////
// Name: mix_linear_burn.mm
// Author:方枫杰
// Date:2012-8-13
// Desc:线性加深，查看每个通道中的颜色信息,
// 通过减小亮度使基色变暗以反映混合色。
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

	if(tex_color.r + target_tex_color.r - 1 > 1)
		out_color.r = 1;
	else if(tex_color.r + target_tex_color.r - 1 < 0)
		out_color.r = 0;
	else
		out_color.r = tex_color.r + target_tex_color.r - 1;

	if(tex_color.g + target_tex_color.g - 1 > 1)
		out_color.g = 1;
	else if(tex_color.g + target_tex_color.g - 1 < 0)
		out_color.g = 0;
	else
		out_color.g = tex_color.g + target_tex_color.g - 1;

	if(tex_color.b + target_tex_color.b - 1 > 1)
		out_color.b = 1;
	else if(tex_color.b + target_tex_color.b - 1 < 0)
		out_color.b = 0;
	else
		out_color.b = tex_color.b + target_tex_color.b - 1;
    
	return out_color;
  
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}