////////////////////////////////////////////////
// Name: mix_multiply.mm
// Author:方枫杰
// Date:2012-8-13
// Desc:正片叠底，查看每个通道中的颜色信息并将基色与混合色复合，
// 结果色是较暗的颜色。任何颜色与黑色混合产生黑色，与白色混合保持不变。
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

    return tex_color * target_tex_color;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}