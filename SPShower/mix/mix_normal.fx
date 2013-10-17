////////////////////////////////////////////////
// Name: mix_normal.mm
// Author:方枫杰
// Date:2012-8-13
// Desc:正常，使用时用当前图层像素的颜色覆盖下层颜色，做α混合。
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

	if(tex_color.a > target_tex_color.a)
		out_color.a = tex_color.a;
	else
		out_color.a = target_tex_color.a;

	out_color.r = (tex_color.a * tex_color.r + (1 - target_tex_color.a) * target_tex_color.r) / out_color.a;
	out_color.g = (tex_color.a * tex_color.g + (1 - target_tex_color.a) * target_tex_color.g) / out_color.a;
	out_color.b = (tex_color.a * tex_color.b + (1 - target_tex_color.a) * target_tex_color.b) / out_color.a;
	out_color.a = tex_color.a + target_tex_color.a;

	if(	   out_color.a > 1 )
	{
		out_color.a = 1;
	}
    
	return out_color;
}

technique T0
{
	pass P0
	{
		PixelShader = compile ps_2_0 Main();
	}
}