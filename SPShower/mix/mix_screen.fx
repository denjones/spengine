////////////////////////////////////////////////
// Name: mix_screen.mm
// Author:方枫杰
// Date:2012-8-14
// Desc:滤色(屏幕)，查看每个通道的颜色信息将混合色的互补色与基色混合。
// 结果色总是较亮的颜色，用黑色过滤时颜色保持不变，用白色过滤将产生白色。
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

    return (1 - (1 - tex_color) * (1 - target_tex_color));
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}